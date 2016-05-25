#include "ch.h"
#include "udc.h"
#include "motor.h"
#include "driving.h"
#include "common.h"

MotorObj M[8] = {{.id=0},{.id=1},{.id=2},
                 {.id=3},{.id=4},{.id=5},
                 {.id=6},{.id=7}};

const motor_setting_t DefaultIdle = {
    .Mode = motor_idle,
    .ScaleFactor = 1.0,
    .AccelerationLimit = 1,
    .SpeedLimit = 600,
    .CommandCycle = 4000,
    .MotorVoltage = 12000,
    .CurrentLimit = 1000,
    .kP = 0,
    .kI = 0,
    .kD = 0,
    .kFF = 0
};

const motor_setting_t DefaultBrake = {
    .Mode = motor_brake,
    .ScaleFactor = 1.0,
    .AccelerationLimit = 1,
    .SpeedLimit = 600,
    .CommandCycle = 4000,
    .MotorVoltage = 12000,
    .CurrentLimit = 1000,
    .kP = 0,
    .kI = 0,
    .kD = 0,
    .kFF = 0
};

const motor_setting_t DefaultVMode = {
    .Mode = motor_Vmode,
    .ScaleFactor = 1.0,
    .AccelerationLimit = 3,
    .SpeedLimit = 600,
    .CommandCycle = 4000,
    .MotorVoltage = 12000,
    .CurrentLimit = 1000,
    .kP = 500,
    .kI = 1,
    .kD = 1,
    .kFF = 0
};

const motor_setting_t DefaultPMode = {
    .Mode = motor_Pmode,
    .ScaleFactor = 10.0,
    .AccelerationLimit = 200,
    .SpeedLimit = 4000,
    .CommandCycle = 4000,
    .MotorVoltage = 12000,
    .CurrentLimit = 1000,
    .kP = 200,
    .kI = 1,
    .kD = 40,
    .kFF = 0
};

const motor_setting_t M0VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,                       //3000
 .kI = 700,                         //1600
 .kD = 50,                       //50
 .kFF = 1500             //1815
};

const motor_setting_t M1VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 700,
 .kD = 50,
 .kFF = 1500             //1800
};

const motor_setting_t M2VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP =2000,
 .kI = 700,
 .kD = 50,
 .kFF = 1500             //1800
};

const motor_setting_t M3VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 700,
 .kD = 50,
 .kFF = 1500,                //1685
};

const motor_setting_t M4VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 800,
 .kD = 50,
 .kFF = 1000
};

const motor_setting_t M5VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 2000,
 .kI = 800,
 .kD = 0,
 .kFF = 1000
};

const motor_setting_t M6VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 14000,
 .kP = 2000,
 .kI = 800,
 .kD = 0,
 .kFF = 1000,
};

const motor_setting_t M7VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 14000,
 .kP = 2000,
 .kI = 800,
 .kD = 0,
 .kFF = 2000,
};

void motor_init(MotorObj *motor, const motor_setting_t *cfg) {
  motor->Setting = *cfg;
}

udc_rx_state_e motor_send_setpoint(MotorObj *motor){
  UDC_Obj_t udc_object;
  if(motor->Setting.Mode == motor_Vmode)
    udc_object.id = CAL_ID_VMODE(motor->id);
  if(motor->Setting.Mode == motor_Pmode)
    udc_object.id = CAL_ID_PMODE(motor->id);
  udc_object.tx_data = (udc_tx_data_t)&(motor->SetPoint);
  udc_object.rx_data = (udc_rx_data_t)&(motor->Feedback);
  udc_object.tx_len = 2;
  udc_object.rx_len = 2;
  udc_object.rx_callback = NULL;
  return UDC_Poll_Single(&udc_object);
}

udc_rx_state_e motor_get_status(MotorObj *motor){
  UDC_Obj_t udc_object;
  udc_object.id = CAL_ID_M_STATUS(motor->id);
  udc_object.rx_data = (udc_rx_data_t)&(motor->Board);
  udc_object.tx_len = 0;
  udc_object.rx_len = 14;
  udc_object.rx_callback = NULL;
  return UDC_Poll_Single(&udc_object);
}

udc_rx_state_e motor_send_setting(MotorObj *motor){
  UDC_Obj_t udc_object;
  udc_object.id = CAL_ID_M_SETTING(motor->id);
  udc_object.tx_data = (udc_tx_data_t)&(motor->Setting);
  udc_object.tx_len = 24;
  udc_object.rx_len = 0;
  udc_object.rx_callback = NULL;
  return UDC_Poll_Single(&udc_object);
}

udc_rx_state_e motor_setIdle(MotorObj *motor){
  UDC_Obj_t udc_object;
  udc_object.id = CAL_ID_M_SETTING(motor->id);
  udc_object.tx_data = (udc_tx_data_t)&DefaultIdle;
  udc_object.tx_len = 24;
  udc_object.rx_len = 0;
  udc_object.rx_callback = NULL;
  return UDC_Poll_Single(&udc_object);
}

udc_rx_state_e motor_setBrake(MotorObj *motor){
  UDC_Obj_t udc_object;
  udc_object.id = CAL_ID_M_SETTING(motor->id);
  udc_object.tx_data = (udc_tx_data_t)&DefaultBrake;
  udc_object.tx_len = 24;
  udc_object.rx_len = 0;
  udc_object.rx_callback = NULL;
  return UDC_Poll_Single(&udc_object);
}

void motor_setAlive( volatile void * arg){
     MotorObj * motor = (MotorObj *) arg;
     motor->Alive = 3;
}

void motor_decAlive(volatile void * arg){
     MotorObj * motor = (MotorObj *) arg;
     if ((motor->Alive) >0)
         (motor->Alive)--;
}

