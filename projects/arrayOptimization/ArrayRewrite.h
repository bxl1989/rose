#ifndef ARRAY_REWRITE_H
#define ARRAY_REWRITE_H

#include <ArrayInterface.h>
#include <AstInterface.h>

class CreateTmpArray
{
  STD map<STD string, AstNodePtr>& varmap;
  STD list<AstNodePtr>& newStmts;
  AstNodePtr model;
 public:
  CreateTmpArray( STD map<STD string, AstNodePtr>& _varmap, STD list<AstNodePtr>& _newstmts) 
     :  newStmts(_newstmts), varmap(_varmap), model() {} 
  AstNodePtr create_tmp_array( AstInterface& fa, const AstNodePtr& arrayExp, const STD string name);
  void set_model_array( const AstNodePtr& mod) { model = mod; }
};

class RewriteConstructArrayAccess 
   : public CreateTmpArray, public MapObject<SymbolicVal, SymbolicVal>
{
  // rewrite reads of construct_array ops to remove implicit array temperaries 
  // rewrite reads of unknown array ops by creating explicit temperaries
  ArrayInterface& anal;
  CPPAstInterface& fa;
public:
  RewriteConstructArrayAccess( CPPAstInterface& _fa, ArrayInterface& a,
                               STD map<STD string, AstNodePtr>& _varmap,
                               STD list<AstNodePtr>& _newstmts)
      : fa(_fa), anal(a), CreateTmpArray(_varmap, _newstmts) {}
  bool rewritable( const SymbolicVal& head);
  SymbolicVal operator()( const SymbolicVal& orig);
};

class RewriteArrayModOp : public TransformAstTree
{
  ArrayInterface& anal;

 public:
  RewriteArrayModOp( ArrayInterface &_op) : anal(_op) {}
  bool operator()(AstInterface& fa, const AstNodePtr& head, AstNodePtr& result);
};

class RewriteToArrayAst : public TransformAstTree
{
  ArrayInterface& anal;

 public:
  RewriteToArrayAst( ArrayInterface &_op) : anal(_op) {}
  bool operator()(AstInterface& fa, const AstNodePtr& head, AstNodePtr& result);
};

class RewriteFromArrayAst : public TransformAstTree
{
  ArrayInterface& anal;
 public:
  RewriteFromArrayAst( ArrayInterface &_op) : anal(_op) {}
  bool operator()(AstInterface& fa, const AstNodePtr& head, AstNodePtr& result);
};

#endif



