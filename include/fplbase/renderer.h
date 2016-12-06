// Copyright 2014 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FPLBASE_RENDERER_H
#define FPLBASE_RENDERER_H

#include "fplbase/config.h"  // Must come first.

#include "fplbase/environment.h"
#include "fplbase/material.h"
#include "fplbase/mesh.h"
#include "fplbase/render_state.h"
#include "fplbase/shader.h"
#include "fplbase/texture.h"
#include "fplbase/version.h"
#include "fplutil/mutex.h"
#include "mathfu/glsl_mappings.h"

namespace fplbase {

class Renderer;

/// @file
/// @addtogroup fplbase_renderer
/// @{

/// @class RendererBase
/// @brief Manages the rendering system, handling the window and resources.
///
/// The core of the rendering system. Deals with setting up and shutting down
/// the window + OpenGL context, and creating/using resources
/// such as shaders, textures, and geometry.
///
/// This is a singleton that has shared ownership amongst all Renderer classes.
/// When the first Renderer class is created, this RendererBase class is also
/// created. When the last Renderer class is destroyed, this RendererBase
/// class is also destroyed.
///
/// Users should instantiate one or more Renderer classes. Users should *not*
/// instantiate RendererBase.
///
/// Users can call a subset of Renderer functionality via the RendererBase
/// singleton. For example,
/// @code{.cpp}
///    if (RendererBase::Get()->feature_level() >= kFeatureLevel30) {
///       // Go ahead and use VAOs (vertex array objects).
///    }
/// @endcode
/// But all of the RendererBase functionality is also in Renderer,
/// and using it may (potentially) be faster since each thread has its own
/// Renderer and there is only one shared RendererBase. So prefer using
/// Renderer over the RendererBase singleton, when you have a Renderer around.
class RendererBase {
 public:
  // Construction and destruction cannot be private since we use
  // std::shared_ptr in Renderer (friend-ing is insufficient), but you should
  // not create your own RendererBase.
  // RendererBase should only be constructed internally.
  RendererBase();
  ~RendererBase();

  /// @brief Initializes the renderer by initializing the Environment object.
  ///
  /// both parameters are used on desktop platforms, but may be ignored on
  /// mobile platforms or certain environment backends in favor of the native
  /// resolution.
  /// Whether this actually still needs to create an context depends on the
  /// backend.
  /// A descriptive error is in last_error() if it returns false.
  ///
  /// @param window_size The default size to initialize the window to.
  /// @param window_title The title of the created window.
  /// @return Returns true on success, false if there was an error.
  bool Initialize(const mathfu::vec2i &window_size, const char *window_title);

  /// @brief Swaps frames. Call this once per frame inside your main loop.
  ///
  /// The two arguments are typically the result of the InputManager's
  /// minimized() and Time() (seconds since the start of the program).
  ///
  /// @param minimized If the window is considered to be minimized.
  /// @param time The seconds since the start of the program.
  void AdvanceFrame(bool minimized, double time);

  /// @brief Cleans up the resources initialized by the renderer.
  void ShutDown() { environment_.ShutDown(); }
  /// @brief Sets the window size, for when window is not owned by the renderer.
  ///
  /// In the non-window-owning use case, call to update the window size whenever
  /// it changes.
  ///
  /// @param window_size The size to set the window to.
  void SetWindowSize(const mathfu::vec2i &window_size) {
    environment_.SetWindowSize(window_size);
  }

  /// @brief Create a shader object from two strings containing glsl code.
  ///
  /// Returns nullptr upon error, with a descriptive message in glsl_error().
  /// Attribute names in the vertex shader should be aPosition, aNormal,
  /// aTexCoord, aColor, aBoneIndices and aBoneWeights, to match whatever
  /// attributes your vertex data has.
  ///
  /// @param vs_source The source code of the vertex shader.
  /// @param ps_source The source code of the fragment shader.
  Shader *CompileAndLinkShader(const char *vs_source, const char *ps_source);

  /// @brief Like CompileAndLinkShader, but pass in an old shader to replace.
  ///
  /// Use `placement new` to use the same memory for the new shader.
  /// Returns nullptr upon error, with a descriptive message in glsl_error().
  /// @note Only call this at the start of the frame.
  ///
  /// @param shader The old shader to replace with the recompiled shader.
  /// @param vs_source The source code of the vertex shader.
  /// @param ps_source The source code of the fragment shader.
  Shader *RecompileShader(const char *vs_source, const char *ps_source,
                          Shader *shader);

  /// @brief Checks for multithreading API.
  /// Returns true if the graphics API allows multi-threading
  bool AllowMultiThreading();

  /// @brief Set bone transforms in vertex shader uniforms.
  ///
  /// Allows vertex shader to skin each vertex to the bone position.
  ///
  /// @param bone_transforms Array of transforms to pass to the shader.
  /// @param num_bones The length of the provided array.
  void SetAnimation(const mathfu::AffineTransform *bone_transforms,
                    int num_bones);

  /// @brief Contains the last error that occurred, if there is one.
  ///
  /// If any of the more complex loading operations (shaders, textures etc.)
  /// fail, this sting will contain a more informative error message.
  ///
  /// @brief Returns the last error that occurred.
  const std::string &last_error() const { return last_error_; }
  void set_last_error(const std::string &last_error) {
    last_error_ = last_error;
  }

  /// @brief The device's current framebuffer size.
  ///
  /// May change from frame to frame due to window resizing or Android
  /// navigation buttons turning on/off.
  ///
  /// @return Returns the current framebuffer size.
  const mathfu::vec2i &window_size() const {
    return environment_.window_size();
  }
  /// @overload mathfu::vec2i &window_size()
  mathfu::vec2i &window_size() { return environment_.window_size(); }

  /// @brief Sets the window size
  ///
  /// Sets the window_size member variable to the given parameter
  /// @param ws The 2D vector for the window size
  void set_window_size(const mathfu::vec2i &ws) {
    environment_.SetWindowSize(ws);
  }

  /// @brief Get the size of the viewport.
  ///
  /// This may be larger than the framebuffer/window on Android if the hardware
  /// scalar is enabled.
  ///
  /// @return Returns the current viewport size.
  mathfu::vec2i GetViewportSize() { return environment_.GetViewportSize(); }

  Environment &environment() { return environment_; }

  /// @brief Time in seconds since program start.
  ///
  /// Used by animated shaders, updated once per frame only.
  ///
  /// @return Returns the time in seconds since program start.
  double time() const { return time_; }

  /// @brief The supported OpenGL ES feature level.
  /// @return Returns the supported OpenGL ES feature level.
  FeatureLevel feature_level() const { return environment_.feature_level(); }

  /// @brief The blend that will be used for all draw calls.
  /// @return Returns the blend mode that will be used.
  BlendMode force_blend_mode() const { return force_blend_mode_; }
  /// @brief Set to override the blend mode used for all draw calls.
  ///
  /// Overrides the blend that was set by calling SetBlendMode.
  /// Set to kBlendModeCount to disable.
  ///
  /// @param bm The blend mode to be used.
  void set_force_blend_mode(BlendMode bm) { force_blend_mode_ = bm; }

  /// @brief Set this force any shader that gets loaded to use this pixel shader
  ///        instead (for debugging purposes).
  /// @param ps The pixel shader that will be used.
  void set_override_pixel_shader(const std::string &ps) {
    override_pixel_shader_ = ps;
  }

  /// @brief Get the max number of uniforms components (i.e. individual floats,
  ///        so a mat4 needs 16 of them).
  ///
  /// The value is in individual floats, so a mat4 needs 16 of them. This
  /// variable is also available in the shader as
  /// GL_MAX_VERTEX_UNIFORM_COMPONENTS. From this, you can compute safe sizes
  /// of uniform arrays etc.
  ///
  /// @return Returns the max number of uniform components.
  int max_vertex_uniform_components() { return max_vertex_uniform_components_; }

  /// @brief Returns the version of the FPL Base Library.
  const FplBaseVersion *GetFplBaseVersion() const { return version_; }

  /// @brief Returns if a texture format is supported by the hardware.
  bool SupportsTextureFormat(TextureFormat texture_format) const;

  /// @brief Returns if a NPOT textures are supported by the hardware.
  /// see: https://www.opengl.org/wiki/NPOT_Texture
  bool SupportsTextureNpot() const;

  // Get current singleton instance.
  static RendererBase *Get() {
    assert(!the_base_weak_.expired());
    return the_base_raw_;
  }

 private:
  friend class Renderer;

  ShaderHandle CompileShader(bool is_vertex_shader, ShaderHandle program,
                             const char *source);
  Shader *CompileAndLinkShaderHelper(const char *vs_source,
                                     const char *ps_source, Shader *shader);

  // Initialize OpenGL parameters like uniform limits, supported texture formats
  // etc.
  bool InitializeRenderingState();

  double time_;

  std::string last_error_;

  Environment environment_;

  int64_t supports_texture_format_;  // 1 bit for each enum in TextureFormat.

  bool supports_texture_npot_;

  Shader *force_shader_;
  BlendMode force_blend_mode_;
  std::string override_pixel_shader_;

  int max_vertex_uniform_components_;

  // Current version of the library.
  const FplBaseVersion *version_;

  // Singleton instance.
  // Ownership is shared amongst the Renderer classes.
  // Singleton is created when the first Renderer is created, and destroyed
  // when the last Renderer is destroyed.
  static std::weak_ptr<RendererBase> the_base_weak_;

  // There is no way to get the raw pointer from the weak_ptr above, so store it
  // unsafely here. This is necessary to support the Get() call.
  static RendererBase* the_base_raw_;

  // Ensure creation and deletion of singleton is atomic.
  static fplutil::Mutex the_base_mutex_;
};

/// @class Renderer
/// @brief Renderer is the main API class for rendering commands.
///
/// Graphics APIs that support multi-threading (e.g. Vulkan) can have multiple
/// Renderer classes, one for each thread. Non-multi-threaded APIs (e.g. OpenGL)
/// should avoid using two Renderer classes at the same time, though it's
/// valid for more than one to exist.
class Renderer {
 public:
  Renderer();
  ~Renderer();

  /// @brief Shader uniform: model_view_projection
  /// @return Returns the current model view projection being used.
  const mathfu::mat4 &model_view_projection() const {
    return model_view_projection_;
  }
  /// @brief Sets the shader uniform model_view_projection
  /// @param mvp The model view projection to be passed to the shader.
  void set_model_view_projection(const mathfu::mat4 &mvp) {
    model_view_projection_ = mvp;
  }

  /// @brief Shader uniform: model (object to world transform only)
  /// @return Returns the current model transform being used.
  const mathfu::mat4 &model() const { return model_; }
  /// @brief Sets the shader uniform model transform.
  /// @param model The model transform to be passed to the shader.
  void set_model(const mathfu::mat4 &model) { model_ = model; }

  /// @brief Shader uniform: color
  /// @return Returns the current color being used.
  const mathfu::vec4 &color() const { return color_; }
  /// @brief Sets the shader uniform color.
  /// @param color The color to be passed to the shader.
  void set_color(const mathfu::vec4 &color) { color_ = color; }

  /// @brief Shader uniform: light_pos
  /// @return Returns the current light position being used.
  const mathfu::vec3 &light_pos() const { return light_pos_; }
  /// @brief Sets the shader uniform light position.
  /// @param light_pos The light position to be passed to the shader.
  void set_light_pos(const mathfu::vec3 &light_pos) { light_pos_ = light_pos; }

  /// @brief Shader uniform: camera_pos
  /// @return Returns the current camera position being used.
  const mathfu::vec3 &camera_pos() const { return camera_pos_; }
  /// @brief Sets the shader uniform camera position.
  /// @param camera_pos The camera position to be passed to the shader.
  void set_camera_pos(const mathfu::vec3 &camera_pos) {
    camera_pos_ = camera_pos;
  }

  /// @brief Shader uniform: bone_transforms
  /// @return Returns the current array of bone transforms being used.
  const mathfu::AffineTransform *bone_transforms() const {
    return bone_transforms_;
  }
  /// @brief The number of bones in the bone_transforms() array.
  /// @return Returns the length of the bone_transforms() array.
  int num_bones() const { return num_bones_; }
  /// @brief Sets the shader uniform bone transforms.
  /// @param bone_transforms The bone transforms to be passed to the shader.
  /// @param num_bones The length of the bone_transforms array provided.
  void SetBoneTransforms(const mathfu::AffineTransform *bone_transforms,
                         int num_bones) {
    bone_transforms_ = bone_transforms;
    num_bones_ = num_bones;
  }

  /// @brief Clears the framebuffer.
  ///
  /// Call this after AdvanceFrame if desired.
  ///
  /// @param color The color to clear the buffer to.
  void ClearFrameBuffer(const mathfu::vec4 &color);

  /// @brief Clears the depthbuffer. Leaves the colorbuffer untouched.
  /// @param render_context Pointer to the render context
  void ClearDepthBuffer();

  /// @brief Begin rendering commands.
  /// This must be called before any rendering commands are done
  void BeginRendering();

  /// @brief End rendering commands.
  /// This is called after all of the rendering commands are done
  void EndRendering();

  /// @brief Sets the blend mode used by the renderer.
  ///
  /// Set alpha test (cull pixels with alpha below amount) vs alpha blend
  /// (blend with framebuffer pixel regardedless).
  ///
  /// @param blend_mode The type of blend mode, see materials.h for valid enum
  ///                   values.
  /// @param amount The value used with kBlendModeTest, defaults to 0.5f.
  void SetBlendMode(BlendMode blend_mode, float amount);
  /// @overload void SetBlendMode(BlendMode blend_mode)
  void SetBlendMode(BlendMode blend_mode);

  /// @brief Sets the culling mode. By default, no culling happens.
  ///
  /// @param mode The type of culling mode to use.
  void SetCulling(CullingMode mode);

  /// @brief Sets the viewport region.
  ///
  /// @param viewport The viewport region to set.
  void SetViewport(const Viewport &viewport);

  /// @brief Set to compare fragment against Z-buffer before writing, or not.
  ///
  /// @param depth_func The depth function to use.
  void SetDepthFunction(DepthFunction depth_func);

  /// @brief Turn on a scissor region. Arguments are in screen pixels.
  ///
  /// @param pos The lower left corner of the scissor box.
  /// @param size The width and height of the scissor box.s
  void ScissorOn(const mathfu::vec2i &ops, const mathfu::vec2i &size);
  /// @brief Turn off the scissor region.
  void ScissorOff();

  /// @brief Sets the texture to be used for the next draw call
  ///
  /// @param unit The texture unit to set the texture
  /// @param texture Pointer to the texture object
  void SetTexture(unsigned unit, Texture *texture);

  // Forwarded methods from the RendererBase class

  /// @brief Initializes the renderer by initializing the Environment object.
  bool Initialize(const mathfu::vec2i &window_size, const char *window_title) {
    return base_->Initialize(window_size, window_title);
  }

  /// @brief Swaps frames. Call this once per frame inside your main loop.
  void AdvanceFrame(bool minimized, double time) {
    base_->AdvanceFrame(minimized, time);
    SetDepthFunction(kDepthFunctionLess);
  }

  /// @brief Cleans up the resources initialized by the renderer.
  void ShutDown() { base_->ShutDown(); }

  /// @brief Sets the window size, for when window is not owned by the renderer.
  void SetWindowSize(const mathfu::vec2i &window_size) {
    base_->SetWindowSize(window_size);
  }

  /// @brief Create a shader object from two strings containing glsl code.
  Shader *CompileAndLinkShader(const char *vs_source, const char *ps_source) {
    return base_->CompileAndLinkShader(vs_source, ps_source);
  }

  /// @brief Like CompileAndLinkShader, but pass in an old shader to replace.
  Shader *RecompileShader(const char *vs_source, const char *ps_source,
                          Shader *shader) {
    return base_->RecompileShader(vs_source, ps_source, shader);
  }

  /// @brief Checks for multithreading API.
  bool AllowMultiThreading() {
    return (base_->AllowMultiThreading());
  }

  /// @brief Set bone transforms in vertex shader uniforms.
  void SetAnimation(const mathfu::AffineTransform *bone_transforms,
                    int num_bones) {
    base_->SetAnimation(bone_transforms, num_bones);
  }

  /// @brief Contains the last error that occurred, if there is one.
  const std::string &last_error() const {
    return base_->last_error();
  }
  void set_last_error(const std::string &last_error) {
    base_->set_last_error(last_error);
  }

  /// @brief The device's current framebuffer size.
  const mathfu::vec2i &window_size() const {
    return base_->window_size();
  }
  /// @overload mathfu::vec2i &window_size()
  mathfu::vec2i &window_size() { return base_->window_size(); }

  /// @brief Sets the window size
  void set_window_size(const mathfu::vec2i &ws) {
    base_->set_window_size(ws);
  }

  /// @brief Get the size of the viewport.

  mathfu::vec2i GetViewportSize() {
    return base_->GetViewportSize();
  }

  Environment &environment() { return base_->environment(); }

  /// @brief Time in seconds since program start.
  double time() const { return base_->time(); }

  /// @brief The supported OpenGL ES feature level.
  FeatureLevel feature_level() const {
    return base_->feature_level();
  }

  /// @brief The blend that will be used for all draw calls.
  BlendMode force_blend_mode() const {
    return base_->force_blend_mode();
  }
  /// @brief Set to override the blend mode used for all draw calls.
  void set_force_blend_mode(BlendMode bm) {
    base_->set_force_blend_mode(bm);
  }

  /// @brief Set this force any shader that gets loaded to use this pixel shader
  void set_override_pixel_shader(const std::string &ps) {
    base_->set_override_pixel_shader(ps);
  }

  /// @brief Get the max number of uniforms components
  int max_vertex_uniform_components() {
    return base_->max_vertex_uniform_components();
  }

  /// @brief Returns the version of the FPL Base Library.
  const FplBaseVersion *GetFplBaseVersion() const {
    return base_->GetFplBaseVersion();
  }

  /// @brief Returns if a texture format is supported by the hardware.
  bool SupportsTextureFormat(TextureFormat texture_format) const {
    return base_->SupportsTextureFormat(texture_format);
  }

  /// @brief Returns if a NPOT textures are supported by the hardware.
  bool SupportsTextureNpot() const {
    return base_->SupportsTextureNpot();
  }

  MATHFU_DEFINE_CLASS_SIMD_AWARE_NEW_DELETE

  // other render state
  // TODO: move this to private
  Shader *shader_;
  RenderState render_state_;

 private:
  // Shared pointer ensures RendererBase gets deleted once all Renderers are
  // deleted. That is, ownership of RendererBase is shared amongst Renderers.
  std::shared_ptr<fplbase::RendererBase> base_;

  // The mvp. Use the Ortho() and Perspective() methods in mathfu::Matrix
  // to conveniently change the camera.
  mathfu::mat4 model_view_projection_;
  mathfu::mat4 model_;
  mathfu::vec4 color_;
  mathfu::vec3 light_pos_;
  mathfu::vec3 camera_pos_;
  const mathfu::AffineTransform *bone_transforms_;
  int num_bones_;
};

/// @}

}  // namespace fplbase

#endif  // FPLBASE_RENDERER_H
