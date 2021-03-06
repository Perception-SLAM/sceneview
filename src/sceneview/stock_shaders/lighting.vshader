// Stock lighting model.
// Before compiling, one of the following must be #defined and prepended to
// this program:
//    COLOR_PER_VERTEX
//    COLOR_UNIFORM
//
// USE_TEXTURE0 can also be defined to use a texture.

// Input vertex position (model space)
attribute vec4 sv_vert_pos;

// Input vertex normal vector
attribute vec3 sv_normal;

// Model-view-projection matrix
uniform mat4 sv_mvp_mat;

uniform mat4 sv_model_mat;

// Normal vector transformation matrix
uniform mat3 sv_model_normal_mat;

varying vec3 normal;

varying vec3 surface_pos;

#ifdef COLOR_PER_VERTEX
attribute float sv_shininess;
attribute vec4 sv_diffuse;
attribute vec4 sv_specular;

varying float shininess;
varying vec4 diffuse;
varying vec4 specular;
#endif

#ifdef USE_TEXTURE0
// Texture coordinates
attribute vec2 sv_tex_coords_0;

varying vec2 texc_0;
#endif

void main(void)
{
  normal = normalize(sv_model_normal_mat * sv_normal);
  surface_pos = vec3(sv_model_mat * sv_vert_pos);

#ifdef COLOR_PER_VERTEX
  shininess = sv_shininess;
  diffuse = sv_diffuse;
  specular = sv_specular;
#endif

#ifdef USE_TEXTURE0
  texc_0 = sv_tex_coords_0;
#endif

  gl_Position = sv_mvp_mat * sv_vert_pos;
}

// vim: ft=glsl
