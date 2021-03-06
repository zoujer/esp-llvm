//===-- X86TargetObjectFile.h - X86 Object Info -----------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_X86_X86TARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_X86_X86TARGETOBJECTFILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/Target/TargetLoweringObjectFile.h"

namespace llvm {

  /// X86_64MachoTargetObjectFile - This TLOF implementation is used for Darwin
  /// x86-64.
  class X86_64MachoTargetObjectFile : public TargetLoweringObjectFileMachO {
  public:
    const MCExpr *
    getTTypeGlobalReference(const GlobalValue *GV, unsigned Encoding,
                            Mangler &Mang, const TargetMachine &TM,
                            MachineModuleInfo *MMI,
                            MCStreamer &Streamer) const override;

    // getCFIPersonalitySymbol - The symbol that gets passed to
    // .cfi_personality.
    MCSymbol *getCFIPersonalitySymbol(const GlobalValue *GV, Mangler &Mang,
                                      const TargetMachine &TM,
                                      MachineModuleInfo *MMI) const override;

    const MCExpr *getIndirectSymViaGOTPCRel(const MCSymbol *Sym,
                                            const MCValue &MV, int64_t Offset,
                                            MachineModuleInfo *MMI,
                                            MCStreamer &Streamer) const override;
  };

  /// \brief This implemenatation is used for X86 ELF targets that don't
  /// have a further specialization.
  class X86ELFTargetObjectFile : public TargetLoweringObjectFileELF {
  public:
    X86ELFTargetObjectFile() {
      PLTRelativeVariantKind = MCSymbolRefExpr::VK_PLT;
    }

    /// \brief Describe a TLS variable address within debug info.
    const MCExpr *getDebugThreadLocalSymbol(const MCSymbol *Sym) const override;
  };

  /// X86LinuxNaClTargetObjectFile - This implementation is used for linux and
  /// Native Client on x86 and x86-64.
  class X86LinuxNaClTargetObjectFile : public X86ELFTargetObjectFile {
    void Initialize(MCContext &Ctx, const TargetMachine &TM) override;
  };

  /// \brief This implementation is used for Windows targets on x86 and x86-64.
  class X86WindowsTargetObjectFile : public TargetLoweringObjectFileCOFF {
    const MCExpr *
    lowerRelativeReference(const GlobalValue *LHS, const GlobalValue *RHS,
                           Mangler &Mang,
                           const TargetMachine &TM) const override;

    /// \brief Given a mergeable constant with the specified size and relocation
    /// information, return a section that it should be placed in.
    MCSection *getSectionForConstant(const DataLayout &DL, SectionKind Kind,
                                     const Constant *C,
                                     unsigned &Align) const override;
  };

} // end namespace llvm

#endif
