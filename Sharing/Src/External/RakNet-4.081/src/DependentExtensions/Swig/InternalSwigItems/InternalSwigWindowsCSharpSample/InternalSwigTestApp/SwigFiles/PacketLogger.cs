// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace RakNet {

using System;
using System.Runtime.InteropServices;

public class PacketLogger : PluginInterface2 {
  private HandleRef swigCPtr;

  internal PacketLogger(IntPtr cPtr, bool cMemoryOwn) : base(RakNetPINVOKE.PacketLogger_SWIGUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PacketLogger obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PacketLogger() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          RakNetPINVOKE.delete_PacketLogger(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public virtual void FormatLine(ref string preInitializedStringBigEnoughToFitResult, string dir, string type, uint packet, uint frame, byte messageIdentifier, uint bitLen, ulong time, SystemAddress local, SystemAddress remote, uint splitPacketId, uint splitPacketIndex, uint splitPacketCount, uint orderingIndex) {
	preInitializedStringBigEnoughToFitResult=FormatLineHelper( preInitializedStringBigEnoughToFitResult, dir, type,  packet, frame,  messageIdentifier, bitLen,  time, local,  remote, splitPacketId,  splitPacketIndex, splitPacketCount,  orderingIndex);
  }

  public virtual void FormatLine(ref string preInitializedStringBigEnoughToFitResult, string dir, string type, uint packet, uint frame, string idToPrint, uint bitLen, ulong time, SystemAddress local, SystemAddress remote, uint splitPacketId, uint splitPacketIndex, uint splitPacketCount, uint orderingIndex) {
  	preInitializedStringBigEnoughToFitResult=FormatLineHelper( preInitializedStringBigEnoughToFitResult,  dir, type,  packet, frame,  idToPrint, bitLen,  time, local,  remote, splitPacketId,  splitPacketIndex, splitPacketCount,  orderingIndex);
  }

  public static PacketLogger GetInstance() {
    IntPtr cPtr = RakNetPINVOKE.PacketLogger_GetInstance();
    PacketLogger ret = (cPtr == IntPtr.Zero) ? null : new PacketLogger(cPtr, false);
    return ret;
  }

  public static void DestroyInstance(PacketLogger i) {
    RakNetPINVOKE.PacketLogger_DestroyInstance(PacketLogger.getCPtr(i));
  }

  public PacketLogger() : this(RakNetPINVOKE.new_PacketLogger(), true) {
  }

  public virtual void LogHeader() {
    RakNetPINVOKE.PacketLogger_LogHeader(swigCPtr);
  }

  public virtual void WriteLog(string str) {
    RakNetPINVOKE.PacketLogger_WriteLog(swigCPtr, str);
  }

  public virtual void WriteMiscellaneous(string type, string msg) {
    RakNetPINVOKE.PacketLogger_WriteMiscellaneous(swigCPtr, type, msg);
  }

  public virtual void SetPrintID(bool print) {
    RakNetPINVOKE.PacketLogger_SetPrintID(swigCPtr, print);
  }

  public virtual void SetPrintAcks(bool print) {
    RakNetPINVOKE.PacketLogger_SetPrintAcks(swigCPtr, print);
  }

  public virtual void SetPrefix(string _prefix) {
    RakNetPINVOKE.PacketLogger_SetPrefix(swigCPtr, _prefix);
  }

  public virtual void SetSuffix(string _suffix) {
    RakNetPINVOKE.PacketLogger_SetSuffix(swigCPtr, _suffix);
  }

  public static string BaseIDTOString(byte Id) {
    string ret = RakNetPINVOKE.PacketLogger_BaseIDTOString(Id);
    return ret;
  }

  public void SetLogDirectMessages(bool send) {
    RakNetPINVOKE.PacketLogger_SetLogDirectMessages(swigCPtr, send);
  }

  private string FormatLineHelper(string into, string dir, string type, uint packet, uint frame, byte messageIdentifier, uint bitLen, ulong time, SystemAddress local, SystemAddress remote, uint splitPacketId, uint splitPacketIndex, uint splitPacketCount, uint orderingIndex) {
    string ret = RakNetPINVOKE.PacketLogger_FormatLineHelper__SWIG_0(swigCPtr, into, dir, type, packet, frame, messageIdentifier, bitLen, time, SystemAddress.getCPtr(local), SystemAddress.getCPtr(remote), splitPacketId, splitPacketIndex, splitPacketCount, orderingIndex);
    if (RakNetPINVOKE.SWIGPendingException.Pending) throw RakNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  private string FormatLineHelper(string into, string dir, string type, uint packet, uint frame, string idToPrint, uint bitLen, ulong time, SystemAddress local, SystemAddress remote, uint splitPacketId, uint splitPacketIndex, uint splitPacketCount, uint orderingIndex) {
    string ret = RakNetPINVOKE.PacketLogger_FormatLineHelper__SWIG_1(swigCPtr, into, dir, type, packet, frame, idToPrint, bitLen, time, SystemAddress.getCPtr(local), SystemAddress.getCPtr(remote), splitPacketId, splitPacketIndex, splitPacketCount, orderingIndex);
    if (RakNetPINVOKE.SWIGPendingException.Pending) throw RakNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
