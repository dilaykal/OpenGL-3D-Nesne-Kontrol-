#include "shapecreator.hpp"
#include "vertexarrayobject.hpp"
#include "indexbuffer.hpp"
#include "shaderprogram.hpp"
#include "vertexbuffer.hpp"
#include "vertextypes.hpp"
namespace graf
{
    VertexArrayObject* ShapeCreator::create(ShapeTypes shape)
    {
        switch (shape)
        {
        case ShapeTypes::Square:           return createSquare();
            
        case ShapeTypes::Circle:           return createCircle(10);
            
        case ShapeTypes::Cube:             return createCube();

        case ShapeTypes::Pyramid:           return createPyramid();

        case ShapeTypes::TruncatedPyramid:           return createTruncatedPyramid();

        default:
            return nullptr;
            break;
        }
    }
    VertexArrayObject* ShapeCreator::createCircle(int anglesInDegrees)
    {

        if(m_vaoMap.count(ShapeTypes::Circle)>0)
            return m_vaoMap[ShapeTypes::Circle];

        graf::VertexArrayObject *   va = new VertexArrayObject();
        graf::VertexBuffer*         vb = new VertexBuffer();
        graf::IndexBuffer*          ib = new IndexBuffer();
       
        int vertexCount = 360/anglesInDegrees;
        int faceCount = vertexCount-2;

        VertexList vertices;
        IndexList indices;       
        
        for(int i=0;i<vertexCount;i++)
        {
            Vertex vertex;
            
            double currentAngle =anglesInDegrees*i;
            vertex.position.x= glm::cos(glm::radians(currentAngle));
            vertex.position.y = glm::sin(glm::radians(currentAngle));
            vertex.position.z = 0.0f;
            vertex.texture.s = 0.5+0.5*glm::cos(glm::radians(currentAngle));
            vertex.texture.t = 0.5+0.5*glm::sin(glm::radians(currentAngle));
            vertices.emplace_back(vertex);
           
        }
        for(int i=0;i<faceCount;i++)
        {
            indices.emplace_back(0);
            indices.emplace_back(i+2);
            indices.emplace_back(i+1);
        }
        va->create();
        vb->create(&vertices[0],sizeof(Vertex)*vertices.size());      
        ib->create(&indices[0],sizeof(unsigned int)*indices.size());
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addVertexAttribute(graf::VertexAttributeType::Position);
        va->addVertexAttribute(graf::VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::Circle]= va;
        va->unbind();
        return va;
    }
    VertexArrayObject* ShapeCreator::createSquare( )
    {
        if(m_vaoMap.count(ShapeTypes::Square)>0)
            return m_vaoMap[ShapeTypes::Square];

        float vertices[] = {  
        /*   x     y     z     s    t */
        -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
         0.5f, 0.5f, 0.0f, 1.0f,1.0f,
         0.5f,-0.5f, 0.0f, 1.0f,0.0f,

         0.5f,-0.5f, 0.0f, 1.0f,0.0f,   
        -0.5f,-0.5f, 0.0f, 0.0f,0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f,1.0f       
        }; 

        unsigned int indices[]={
            0,1,2,3,4,5
        };
        VertexArrayObject *va = new VertexArrayObject;
        VertexBuffer *vb= new VertexBuffer;
        IndexBuffer *ib = new IndexBuffer;

        vb->create(vertices,sizeof(vertices));
        ib->create(indices,sizeof(indices));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);

        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();
        m_vaoMap[ShapeTypes::Square] =va;
        va->unbind();

        return va;
    }
    VertexArrayObject* ShapeCreator::createCube()
    {
        if(m_vaoMap.count(ShapeTypes::Cube)>0)
            return m_vaoMap[ShapeTypes::Cube];

        glm::vec3 positions[] = {  
            {-0.5f,  0.5f, 0.5f},
            { 0.5f,  0.5f, 0.5f},
            { 0.5f, -0.5f, 0.5f},
            {-0.5f, -0.5f, 0.5f},

            {-0.5f, 0.5f, -0.5f},
            {0.5f,  0.5f,  -0.5f},
            {0.5f, -0.5f, -0.5f},
            {-0.5f,-0.5f,-0.5f}        
        }; 


        int vertexCount = 24;
        Vertex* vertices= new Vertex[vertexCount];
        std::vector<unsigned int> indices;


        //Ön Yüz
        vertices[0].position = positions[0];
        vertices[1].position = positions[1];
        vertices[2].position = positions[2];
        vertices[3].position = positions[3];

        vertices[0].texture = glm::vec2(0.0f,1.0f);
        vertices[1].texture = glm::vec2(1.0f,1.0f);
        vertices[2].texture = glm::vec2(1.0f,0.0f);
        vertices[3].texture = glm::vec2(0.0f,0.0f);


        //Sağ Yüz
        vertices[4].position = positions[1];
        vertices[5].position = positions[5];
        vertices[6].position = positions[6];
        vertices[7].position = positions[2];

        vertices[4].texture = glm::vec2(0.0f,1.0f);
        vertices[5].texture = glm::vec2(1.0f,1.0f);
        vertices[6].texture = glm::vec2(1.0f,0.0f);
        vertices[7].texture = glm::vec2(0.0f,0.0f);



        //Üst Yüz
        vertices[8].position = positions[4];
        vertices[9].position = positions[5];
        vertices[10].position = positions[1];
        vertices[11].position = positions[0];

        vertices[8].texture = glm::vec2(0.0f,1.0f);
        vertices[9].texture = glm::vec2(1.0f,1.0f);
        vertices[10].texture = glm::vec2(1.0f,0.0f);
        vertices[11].texture = glm::vec2(0.0f,0.0f);

        //Sol Yüz
        vertices[12].position = positions[4];
        vertices[13].position = positions[0];
        vertices[14].position = positions[3];
        vertices[15].position = positions[7];

        vertices[12].texture = glm::vec2(0.0f,1.0f);
        vertices[13].texture = glm::vec2(1.0f,1.0f);
        vertices[14].texture = glm::vec2(1.0f,0.0f);
        vertices[15].texture = glm::vec2(0.0f,0.0f);

        //Arka Yüz
        vertices[16].position = positions[5];
        vertices[17].position = positions[4];
        vertices[18].position = positions[7];
        vertices[19].position = positions[6];

        vertices[16].texture = glm::vec2(0.0f,1.0f);
        vertices[17].texture = glm::vec2(1.0f,1.0f);
        vertices[18].texture = glm::vec2(1.0f,0.0f);
        vertices[19].texture = glm::vec2(0.0f,0.0f);

        //Alt Yüz
        vertices[20].position = positions[3];
        vertices[21].position = positions[2];
        vertices[22].position = positions[6];
        vertices[23].position = positions[7];

        vertices[20].texture = glm::vec2(0.0f,1.0f);
        vertices[21].texture = glm::vec2(1.0f,1.0f);
        vertices[22].texture = glm::vec2(1.0f,0.0f);
        vertices[23].texture = glm::vec2(0.0f,0.0f);
        for(int i=0;i<6;i++)
        {
            indices.push_back(i*4);
            indices.push_back(i*4+2);
            indices.push_back(i*4+1);

            indices.push_back(i*4);
            indices.push_back(i*4+3);
            indices.push_back(i*4+2);            
        }

        VertexArrayObject *va = new VertexArrayObject;
        VertexBuffer *vb= new VertexBuffer;
        IndexBuffer *ib = new IndexBuffer;

        vb->create(vertices,sizeof(Vertex)*vertexCount);
        ib->create(indices.data(),indices.size()*sizeof(unsigned int));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);

        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();
        m_vaoMap[ShapeTypes::Cube] =va;
        va->unbind();

        return va;        
    }
    VertexArrayObject* ShapeCreator::createPyramid()
    {
        if (m_vaoMap.count(ShapeTypes::Pyramid) > 0) {
            return m_vaoMap[ShapeTypes::Pyramid];
        }

        // 5 vertex için array oluştur (4 taban köşesi + 1 tepe nokta)
        const int vertexCount = 5;
        Vertex vertices[vertexCount];

        // Taban köşeleri
        vertices[0].position = glm::vec3(-0.5f, -0.5f, -0.5f);
        vertices[0].texture = glm::vec2(0.0f, 0.0f);

        vertices[1].position = glm::vec3(0.5f, -0.5f, -0.5f);
        vertices[1].texture = glm::vec2(1.0f, 0.0f);

        vertices[2].position = glm::vec3(0.5f, -0.5f, 0.5f);
        vertices[2].texture = glm::vec2(1.0f, 1.0f);

        vertices[3].position = glm::vec3(-0.5f, -0.5f, 0.5f);
        vertices[3].texture = glm::vec2(0.0f, 1.0f);

        // Tepe nokta
        vertices[4].position = glm::vec3(0.0f, 0.5f, 0.0f);
        vertices[4].texture = glm::vec2(0.5f, 0.5f);

        // İndeksler
        unsigned int indices[] = {
            // Taban
            0, 1, 2,
            2, 3, 0,
            // Yan yüzeyler
            0, 1, 4,
            1, 2, 4,
            2, 3, 4,
            3, 0, 4
        };

        VertexArrayObject* va = new VertexArrayObject();
        VertexBuffer* vb = new VertexBuffer();
        IndexBuffer* ib = new IndexBuffer();

        vb->create(vertices, sizeof(Vertex) * vertexCount);
        ib->create(indices, sizeof(indices));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::Pyramid] = va;
        va->unbind();

        return va;
    }
    VertexArrayObject* ShapeCreator::createTruncatedPyramid()
    {
        if (m_vaoMap.count(ShapeTypes::TruncatedPyramid) > 0) {
            return m_vaoMap[ShapeTypes::TruncatedPyramid];
        }

        // Alt taban ve üst taban için ölçekler
        float bottomScale = 1.0f;
        float topScale = 0.6f;  // Üst tabanın alt tabana göre küçültme oranı
        float height = 1.0f;
        
        // 8 köşe noktası için vertex array (4 alt + 4 üst köşe)
        const int vertexCount = 24;  // Her yüz için ayrı vertexler (texture koordinatları için)
        Vertex vertices[vertexCount];
        
        // Alt taban köşeleri
        glm::vec3 bottomVertices[4] = {
            glm::vec3(-0.5f * bottomScale, -0.5f * height, -0.5f * bottomScale),  // Sol arka
            glm::vec3(0.5f * bottomScale, -0.5f * height, -0.5f * bottomScale),   // Sağ arka
            glm::vec3(0.5f * bottomScale, -0.5f * height, 0.5f * bottomScale),    // Sağ ön
            glm::vec3(-0.5f * bottomScale, -0.5f * height, 0.5f * bottomScale)    // Sol ön
        };
        
        // Üst taban köşeleri
        glm::vec3 topVertices[4] = {
            glm::vec3(-0.5f * topScale, 0.5f * height, -0.5f * topScale),  // Sol arka
            glm::vec3(0.5f * topScale, 0.5f * height, -0.5f * topScale),   // Sağ arka
            glm::vec3(0.5f * topScale, 0.5f * height, 0.5f * topScale),    // Sağ ön
            glm::vec3(-0.5f * topScale, 0.5f * height, 0.5f * topScale)    // Sol ön
        };

        // Alt taban
        for (int i = 0; i < 4; i++) {
            vertices[i].position = bottomVertices[i];
            vertices[i].texture = glm::vec2((i == 1 || i == 2) ? 1.0f : 0.0f, 
                                        (i == 2 || i == 3) ? 1.0f : 0.0f);
        }

        // Üst taban
        for (int i = 0; i < 4; i++) {
            vertices[i + 4].position = topVertices[i];
            vertices[i + 4].texture = glm::vec2((i == 1 || i == 2) ? 1.0f : 0.0f, 
                                            (i == 2 || i == 3) ? 1.0f : 0.0f);
        }

        // Yan yüzeyler
        for (int i = 0; i < 4; i++) {
            int baseIndex = 8 + (i * 4);
            int nextI = (i + 1) % 4;

            // Her yan yüz için 4 vertex
            vertices[baseIndex].position = bottomVertices[i];
            vertices[baseIndex + 1].position = bottomVertices[nextI];
            vertices[baseIndex + 2].position = topVertices[nextI];
            vertices[baseIndex + 3].position = topVertices[i];

            // Texture koordinatları
            vertices[baseIndex].texture = glm::vec2(0.0f, 0.0f);
            vertices[baseIndex + 1].texture = glm::vec2(1.0f, 0.0f);
            vertices[baseIndex + 2].texture = glm::vec2(1.0f, 1.0f);
            vertices[baseIndex + 3].texture = glm::vec2(0.0f, 1.0f);
        }

        // İndeksler
        std::vector<unsigned int> indices;
        
        // Alt taban
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(0);

        // Üst taban
        indices.push_back(4);
        indices.push_back(6);
        indices.push_back(5);
        indices.push_back(4);
        indices.push_back(7);
        indices.push_back(6);

        // Yan yüzeyler
        for (int i = 0; i < 4; i++) {
            int baseIndex = 8 + (i * 4);
            indices.push_back(baseIndex);
            indices.push_back(baseIndex + 1);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex);
            indices.push_back(baseIndex + 2);
            indices.push_back(baseIndex + 3);
        }

        VertexArrayObject* va = new VertexArrayObject();
        VertexBuffer* vb = new VertexBuffer();
        IndexBuffer* ib = new IndexBuffer();

        vb->create(vertices, sizeof(vertices));
        ib->create(indices.data(), indices.size() * sizeof(unsigned int));
        va->create();
        va->setVertexBuffer(vb);
        va->setIndexBuffer(ib);
        va->addVertexAttribute(VertexAttributeType::Position);
        va->addVertexAttribute(VertexAttributeType::Texture);
        va->activateAttributes();

        m_vaoMap[ShapeTypes::TruncatedPyramid] = va;
        va->unbind();

        return va;
    }
}