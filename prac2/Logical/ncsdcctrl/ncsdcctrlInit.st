
PROGRAM _INIT

(* ### BEGIN gAxis01 ### *)
      
(* initialize general interfaces *)
      gAxis01.size := gAxis01.size;
      gAxis01_HW.DrvIf_Typ := ncSDC_DRVSM16;
      brsstrcpy( ADR(gAxis01_HW.DrvIf_Name[0]), ADR('gAxis01_DrvIf') );
      gAxis01_HW.DiDoIf_Typ := ncSDC_DIDO;
      brsstrcpy( ADR(gAxis01_HW.DiDoIf_Name[0]), ADR('gAxis01_DiDoIf') );
      gAxis01_HW.EncIf1_Typ := ncSDC_ENC16;
      brsstrcpy( ADR(gAxis01_HW.EncIf1_Name[0]), ADR('gAxis01_EncIf1') );
      gAxis01_EncIf1.iLifeCnt := gAxis01_EncIf1.iLifeCnt;
      
(* initialize old-value for delta step calculation *)
      gAxis01_oSetPosOld := gAxis01_DrvIf.oSetPos;
       
(* ### END gAxis01 ### *)

END_PROGRAM

