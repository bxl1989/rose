
#ifndef LOOP_TREE_LOCALITY
#define LOOP_TREE_LOCALITY

#include <LoopTreeDepComp.h>

struct DepCompAstRef { 
  AstNodePtr orig; 
  LoopTreeNode* stmt; 
  DepCompAstRef(const AstNodePtr& o, LoopTreeNode* s) 
       : orig(o),stmt(s) {}
  STD string ToHandle() const;
  STD string toString() const;
};

class DepCompAstRefGraphNode : public MultiGraphElemTemplate<DepCompAstRef> 
{
 public:
  DepCompAstRefGraphNode(MultiGraphCreate* c, const DepCompAstRef& r)
    : MultiGraphElemTemplate<DepCompAstRef>(c, r) {}
  STD string toString() const { return GetInfo().toString(); }
};

class DepCompAstRefAnal
{
  typedef STD map<LoopTreeNode*, int, STD less<LoopTreeNode*> > StmtMap;
  typedef STD map<AstNodePtr,int, STD less<AstNodePtr> > RefMap;
  StmtMap stmtmap;
  RefMap refmap;
  LoopTreeNode* root;
  
    int get_ref_index( const AstNodePtr& ref) const
       { 
            RefMap:: const_iterator p = refmap.find(ref); 
            assert(p  != refmap.end());
            int res =  (*p).second; 
            return (res > 0)? res : -res;
       }
    void Append( LoopTransformInterface& ai, LoopTreeNode* root);
  public:
    DepCompAstRefAnal(LoopTransformInterface& ai,  LoopTreeNode* _root) 
         : root(_root) { Append(ai, root); }

    LoopTreeNode* get_tree_root() const { return root; }
    int get_stmt_size() const { return stmtmap.size(); }
    bool has_stmt(LoopTreeNode* s) const { return stmtmap.find(s) != stmtmap.end(); } 
    bool is_mod_ref( const AstNodePtr& ref) const
       {
            RefMap:: const_iterator p = refmap.find(ref); 
            assert(p  != refmap.end());
            return  (*p).second < 0; 
       }

    int CompareStmt( LoopTreeNode* s1, LoopTreeNode* s2)  const
      { 
         StmtMap:: const_iterator p1 = stmtmap.find(s1), p2 = stmtmap.find(s2); 
         assert(p1  != stmtmap.end() && p2 != stmtmap.end());
         int i1 = (*p1).second, i2 = (*p2).second; 
         return (i1 == i2)? 0 : ( (i1 < i2)? -1 : 1);
      }
    int CompareAstRef( const DepCompAstRef& r1, const DepCompAstRef& r2) const
      {
         int res = CompareStmt(r1.stmt,r2.stmt);
         if (res == 0 && r1.orig != r2.orig) {
             res = (get_ref_index(r1.orig) < get_ref_index(r2.orig))? -1 : 1;
         }
         return res;
      }
};

class LoopTreeLocalityAnal 
{
  LoopTreeDepCompCreate& comp;
  DepInfoAnal& anal;
  LoopTreeDepGraphCreate inputCreate;
  LoopTransformInterface &fa;

  void ComputeInputDep( LoopTreeDepGraph::NodeIterator iter, DepCompAstRefAnal& stmtorder);
  void ComputeInputDep( LoopTreeDepGraph::NodeIterator src,
                        LoopTreeDepGraph::NodeIterator snk, DepCompAstRefAnal& stmtorder);
  void ComputeInputDep( LoopTreeDepGraphNode *n1, LoopTreeDepGraphNode *n2, 
                        DepCompAstRefAnal& stmtorder);
 public:
  typedef STD set<AstNodePtr, STD less<AstNodePtr> > AstNodeSet;
  LoopTreeLocalityAnal( LoopTransformInterface& _fa, LoopTreeDepCompCreate& c);
  ~LoopTreeLocalityAnal();

  LoopTreeDepGraph* GetInputGraph() { return &inputCreate; }
  LoopTreeDepComp& GetDepComp() { return comp; }

  float SelfSpatialReuses( LoopTreeNode *n, int loop, int linesize);
  int TemporaryReuseRefs(LoopTreeNode *s1, int loop1, LoopTreeNode *s2, int loop2,
                   AstNodeSet &refSet, int reuseDist);
   LoopTransformInterface& GetLoopTransformInterface() { return fa; }
};

class DepCompAstRefGraphCreate: public DepInfoGraphCreate<DepCompAstRefGraphNode> 
{
  typedef STD map<DepCompAstRef, DepCompAstRefGraphNode*, STD less<DepCompAstRef> > AstRefNodeMap; 
  AstRefNodeMap refNodeMap; 

 public:
  DepCompAstRefGraphNode* 
        CreateNode(const AstNodePtr& r, LoopTreeNode* stmt);
  DepInfoEdge* 
      CreateEdge( DepCompAstRefGraphNode* src,  DepCompAstRefGraphNode* snk, const DepInfo& dep);
  void Build(LoopTransformInterface& la, LoopTreeLocalityAnal& tc, LoopTreeNode* root) ;

  bool SelfReuseLevel( const DepCompAstRefGraphNode* n, int level) const;
};

#endif
