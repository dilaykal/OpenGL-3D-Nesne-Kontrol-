#version 330 core                                 
                                    
out vec4 fragColor;  

in vec2 texCoord;  // vertex shader'daki isimle aynı olmalı

uniform sampler2D uTexture;  // C++ kodunda kullanılan isimle aynı olmalı

void main()                                            
{                                                      
   fragColor = texture(uTexture, texCoord);                                  
}