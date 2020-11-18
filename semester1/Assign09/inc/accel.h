//
// COMP-GENG 421 - Shaydon Bodemar
//
// Navigation switch module header
//

#ifndef ACCEL_H_
#define ACCEL_H_

void AccelInit(void);
void AccelClock(void);
Bool TiltedForward(void);
void ClearTiltedForward(void);
Bool TiltedBackward(void);
void ClearTiltedBackward(void);
Bool TiltedRight(void);
void ClearTiltedRight(void);
Bool TiltedLeft(void);
void ClearTiltedLeft(void);


#endif	//ACCEL_H_
