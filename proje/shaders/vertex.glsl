#version 330 core                      
layout (location = 0) in vec3 inPosition;  
layout (location = 1) in vec2 inTexCoord;  

uniform mat4 uWorldTransform;
out vec2 texCoord;  // fragment shader'da da aynı ismi kullanın

void main()                                
{                     
   gl_Position = uWorldTransform * vec4(inPosition, 1.0);  // 2.0 yerine 1.0 kullanın    
   texCoord = inTexCoord;
}