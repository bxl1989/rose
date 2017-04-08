

#ifndef __BinCompass_interruptanalysis__
#define __BinCompass_interruptanalysis__

#include "RoseBin_DataFlowAbstract.h"

class InterruptAnalysis : public RoseBin_DataFlowAbstract {

 public:
 InterruptAnalysis(GraphAlgorithms* algo):RoseBin_DataFlowAbstract(algo)  {}
  ~InterruptAnalysis() {}

  bool run(std::string& name, SgGraphNode* node,
           SgGraphNode* previous) ROSE_DEPRECATED("no longer supported");

  void getValueForDefinition(std::vector<uint64_t>& vec,
                             std::vector<uint64_t>& positions,
                             uint64_t& fpos,
                             SgGraphNode* node,
                             std::pair<X86RegisterClass, int> reg ) ROSE_DEPRECATED("no longer supported");

  std::string getIntCallName_Linux32bit(uint64_t rax,RoseBin_DataTypes::DataTypes& data_ebx,
                                        RoseBin_DataTypes::DataTypes& data_ecx,
                                        RoseBin_DataTypes::DataTypes& data_edx,
                                        std::vector<uint64_t>& val_rbx,
                                        std::vector<uint64_t>& val_rcx,
                                        std::vector<uint64_t>& val_rdx,
                                        std::vector<uint64_t>& pos_ebx,
                                        std::vector<uint64_t>& pos_ecx,
                                        std::vector<uint64_t>& pos_edx,
                                        uint64_t fpos_rbx, uint64_t fpos_rcx, uint64_t fpos_rdx) ROSE_DEPRECATED("no longer supported");
  std::string getIntCallName_Linux64bit(uint64_t rax,RoseBin_DataTypes::DataTypes& data_ebx,
                                        RoseBin_DataTypes::DataTypes& data_ecx,
                                        RoseBin_DataTypes::DataTypes& data_edx,
                                        std::vector<uint64_t>& val_rbx,
                                        std::vector<uint64_t>& val_rcx,
                                        std::vector<uint64_t>& val_rdx,
                                        std::vector<uint64_t>& pos_ebx,
                                        std::vector<uint64_t>& pos_ecx,
                                        std::vector<uint64_t>& pos_edx,
                                        uint64_t fpos_rbx, uint64_t fpos_rcx, uint64_t fpos_rdx) ROSE_DEPRECATED("no longer supported");
  std::string getIntCallName(uint64_t rax,RoseBin_DataTypes::DataTypes& data_ebx,
                             RoseBin_DataTypes::DataTypes& data_ecx,
                             RoseBin_DataTypes::DataTypes& data_edx,
                             std::vector<uint64_t>& val_rbx,
                             std::vector<uint64_t>& val_rcx,
                             std::vector<uint64_t>& val_rdx,
                             std::vector<uint64_t>& pos_ebx,
                             std::vector<uint64_t>& pos_ecx,
                             std::vector<uint64_t>& pos_edx,
                             uint64_t fpos_rbx, uint64_t fpos_rcx, uint64_t fpos_rdx) ROSE_DEPRECATED("no longer supported");

  bool runEdge(SgGraphNode* node, SgGraphNode* next) ROSE_DEPRECATED("no longer supported") {
    return false;
  }

  void init(RoseBin_Graph* vg) ROSE_DEPRECATED("no longer supported") {
    vizzGraph = vg;
  }

};

#endif

