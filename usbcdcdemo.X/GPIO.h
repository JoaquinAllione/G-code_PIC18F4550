/* 
 * File:   GPIO.h
 * Author: joaqu
 *
 * Created on 25 de noviembre de 2021, 19:51
 */

#ifndef GPIO_H
#define	GPIO_H

typedef enum{
    Full_Step = 0,
    Half_Step,
    Quater_Step,
    Eighth_Step,
    Sixtheenth_Step,
}MicroStep_enum;

typedef enum{
    Axis_X = 0,
    Axis_Y,
    Axis_Z,
    All_Axes,
}Axes_enum;


void MicroStepConfig_Get(MicroStep_enum);
MicroStep_enum MicroStepConfig_Set(MicroStep_enum);
void Enable_Axes(Axes_enum);
void Disable_Axes(Axes_enum);
void DirectionConfig_Set(Axes_enum, int);
void GPIO_Init(void);

#endif	/* GPIO_H */

