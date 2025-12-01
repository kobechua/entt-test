//
// Class for renderable objects
// Objects will inherit from this class

class Renderable
{
   public:
      Renderable();

      void Init();

      void AddMesh( Mesh* );
      void AddMesh( Mesh* );
      void AddMesh( Mesh* );
      void AddMesh( Mesh* );

      void UpdateBuffer();

      void Load();
      void Unload();

      ~Renderable();

   private:

}
