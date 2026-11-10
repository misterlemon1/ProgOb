
PROGRAM _CYCLIC

(* ### BEGIN gAxis01 ### *)
      
(* life counter emulation of digital inputs *)
      gAxis01_DiDoIf.iLifeCntReference := gAxis01_DiDoIf.iLifeCntReference + 1;
      gAxis01_DiDoIf.iLifeCntNegHwEnd  := gAxis01_DiDoIf.iLifeCntNegHwEnd  + 1;
      gAxis01_DiDoIf.iLifeCntPosHwEnd  := gAxis01_DiDoIf.iLifeCntPosHwEnd  + 1;
       
(* default function model of ACOPOSmicro: convert absolute steps to delta steps - overflow save delta calculation *)
      gAxis01_MotorStep0 := gAxis01_DrvIf.oSetPos - gAxis01_oSetPosOld;
      gAxis01_oSetPosOld := gAxis01_DrvIf.oSetPos;
       
(* ### END gAxis01 ### *)

END_PROGRAM

