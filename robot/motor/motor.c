#include "ch.h"
#include "udc.h"
#include "motor.h"


MotorObj M[8] = {{.id=0},{.id=1},{.id=2},{.id=3},{.id=4},{.id=5},{.id=6},{.id=7}};

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
  udc_object.rx_len = 10;
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

