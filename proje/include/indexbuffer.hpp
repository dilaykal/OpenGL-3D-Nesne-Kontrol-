#ifndef indexbuffer_hpp
#define indexbuffer_hpp

namespace graf
{
    class IndexBuffer
    {
    public:
        void create(void* data,int size);
        void bind();
        void unbind();
        void release();
        int indexCount()const;
    private:
        unsigned int m_id;
        int m_IndexCount;
    };
}


#endif