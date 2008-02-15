#ifndef TEST_PARALLEL_LOOP
#define TEST_PARALLEL_LOOP

#include <AnnotCollect.h>
#include <OperatorAnnotation.h>
#include <set>

class AstNodePtr;

class ContainerCollection : public TypeAnnotCollection <BoolDescriptor>
{
  virtual bool read_annot_name( const STD string& abname) const
    { return (abname == "container"); }
 public:
  void Dump() const
    { STD cerr << "containers: \n"; TypeAnnotCollection<BoolDescriptor>::Dump(); }
};

class TestParallelLoop  {
  ContainerCollection containers;
  OperatorModInfoCollection modInfo;
  STD map <STD string, OperatorDeclaration> decl;

 public:
  TestParallelLoop( int argc, char** argv); 
  
  bool LoopParallelizable( CPPAstInterface& fa, const AstNodePtr& loop);
  static void DumpOptions( STD ostream& os);

  bool known_operator( AstInterface& fa, const AstNodePtr& fcall,
                        OperatorSideEffectDescriptor& info) 
    { return modInfo.known_operator(fa, fcall, 0, &info); }
  bool known_operator( STD string op) 
         { return modInfo.known_type(op); }
  void Dump() const 
     { 
        containers.Dump(); 
        modInfo.Dump(); 
      }
};

#endif
