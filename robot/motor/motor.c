#include "ch.h"
#include "motor.h"
#include "driving.h"
#include "common.h"
#include "string.h"

MotorObj M[8] = {{.id=0, .timeout=0},{.id=1,.timeout=0},{.id=2,.timeout=0},
                 {.id=3,.timeout=0},{.id=4,.timeout=0},{.id=5,.timeout=0},
                 {.id=6,.timeout=0},{.id=7,.timeout=0}};

motor_2016_t m[8] = {{.id=0,.timeout=0},{.id=1,.timeout=0},{.id=2,.timeout=0},
					{.id=3,.timeout=0},{.id=4,.timeout=0},{.id=5,.timeout=0},
					{.id=6,.timeout=0},{.id=7,.timeout=0}};


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

const motor_setting_t M0VMode = {	//base motor
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 6000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 12000,
 .kP = 2000,                       //3000
 .kI = 700,                         //1600
 .kD = 50,                       //50
 .kFF = 1500             //1815
};

const motor_setting_t M1VMode = {	//base motor
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 6000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 12000,
 .kP = 2000,
 .kI = 700,
 .kD = 50,
 .kFF = 1500             //1800
};

const motor_setting_t M2VMode = {	//linear actuator
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 4500,
 .kI = 00,
 .kD = 0,
 .kFF = 2500,
};

const motor_setting_t M3VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = ChassisScaleFactor,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = (int) (RearWheelSamplingTime * 1000),
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 4500,
 .kI = 00,
 .kD = 0,
 .kFF = 2500,                //1685
};

const motor_setting_t M4VMode = {	//for new maxon shooter
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
// .kP = 5000,
// .kI = 0,
// .kD = 0,
// .kFF = 0
 .kP = 1600,
 .kI = 600,
 .kD = 0,
 .kFF = 400
};

const motor_setting_t M5VMode = {	///for new maxon shooter
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 4000,
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
// .kP = 5000,
// .kI = 0,
// .kD = 0,
// .kFF = 0
 .kP = 1600,
 .kI = 600,
 .kD = 0,
 .kFF = 400
};

const motor_setting_t M6VMode = {
 .Mode = motor_Vmode,
 .ScaleFactor = 1,
 .AccelerationLimit = 1,
 .SpeedLimit = 5000,
 .CommandCycle = 1000,
 .MotorVoltage = 12000,
 .CurrentLimit = 10000,
 .kP = 1600,
 .kI = 600,
 .kD = 0,
 .kFF = 400,
};

const motor_setting_t M6PMode = {
    .Mode = motor_Pmode,
    .ScaleFactor = 100.0,
    .AccelerationLimit = 200,
    .SpeedLimit = 1000,
    .CommandCycle = (int) (RearWheelSamplingTime * 1000),
    .MotorVoltage = 12000,
    .CurrentLimit = 5000,
    .kP = 200,
    .kI = 1,
    .kD = 40,
    .kFF = 0
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
  UDC_Obj_t object;
  if(motor->Setting.Mode == motor_Vmode)
    object.id = CAL_ID_VMODE(motor->id);
  if(motor->Setting.Mode == motor_Pmode)
    object.id = CAL_ID_PMODE(motor->id);
  object.tx_data = (uint8_t*)&(motor->SetPoint);
  object.rx_data = (uint8_t*)&(motor->Feedback);
  object.tx_len = 2;
  object.rx_len = 2;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UMD_Poll_Single(&object);
}

//<<<<<<< HEAD
//udc_rx_state_e motor_get_status(MotorObj *motor){
//  UDC_Obj_t udc_object;
//  udc_object.id = CAL_ID_M_STATUS(motor->id);
//  udc_object.rx_data = (udc_rx_data_t)&(motor->Board);
//  udc_object.tx_len = 0;
//  udc_object.rx_len = 14;
//  udc_object.rx_callback = NULL;
//  return UDC_Poll_Single(&udc_object);
//=======
udc_rx_state_e motor_get_status(MotorObj *motor){
  UDC_Obj_t object;
  object.id = CAL_ID_M_STATUS(motor->id);
  object.rx_data = (uint8_t*)&(motor->Board);
  object.tx_len = 0;
  object.rx_len = 14;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UDC_Poll_Single(&object);
//>>>>>>> b1ab300e10eec07a0da4c8f514d46b53bed302ea
}

udc_rx_state_e motor_send_setting(MotorObj *motor){
  UDC_Obj_t object;
  object.id = CAL_ID_M_SETTING(motor->id);
  object.tx_data = (uint8_t*)&(motor->Setting);
  object.tx_len = 24;
  object.rx_len = 0;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UDC_Poll_Single(&object);
}

udc_rx_state_e motor_setIdle(MotorObj *motor){
  UDC_Obj_t object;
  motor_setting_t setting;
  memcpy(&setting, &(motor->SetPoint), sizeof(motor_setting_t));
  setting.Mode = motor_idle;
  object.id = CAL_ID_M_SETTING(motor->id);
  object.tx_data = (uint8_t*)&setting;
  object.tx_len = 24;
  object.rx_len = 0;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UDC_Poll_Single(&object);
}

udc_rx_state_e motor_setBrake(MotorObj *motor){
  UDC_Obj_t object;
  object.id = CAL_ID_M_SETTING(motor->id);
  object.tx_data = (uint8_t*)&DefaultBrake;
  object.tx_len = 24;
  object.rx_len = 0;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UMD_Poll_Single(&object);
}

void motor_setAlive(void * arg){
     MotorObj * motor = (MotorObj *) arg;
     motor->timeout = 3;
}

void motor_decAlive(void * arg){
     MotorObj * motor = (MotorObj *) arg;
     if ((motor->timeout) >0)
         (motor->timeout)--;
}

//new stuff for 2016 motor board

const motor_setting_2016_t DefaultIdle_2016 = {
    .mode = UNLOCK,
    .curvetype = 0,
    .bandwidth = 20.0,
    .max_jerk_krpmps2 = 20.0,
    .max_accel_krpmps = 20.0,
    .max_speed_krpm = 1.0,
    .max_current_A = 2.0
};

const motor_setting_2016_t DefaultVMode_2016 = {
    .mode = VMODE,
    .curvetype = 0,
    .bandwidth = 40.0,
    .max_jerk_krpmps2 = 300.0,
    .max_accel_krpmps = 100.0,
    .max_speed_krpm = 14.0,
    .max_current_A = 5.0
};

const motor_setting_2016_t DefaultPMode_2016 = {
    .mode = PMODE,
    .curvetype = 2,
    .bandwidth = 50.0,
    .max_jerk_krpmps2 = 300.0,
    .max_accel_krpmps = 50.0,
    .max_speed_krpm = 5.0,
    .max_current_A = 2.0
};

void motor_init_2016(motor_2016_t *motor, const motor_setting_2016_t *cfg) {
  motor->setting = *cfg;
}

udc_rx_state_e motor_send_setpoint_2016(motor_2016_t *motor){
	UDC_Obj_t object;
  if(motor->setting.mode == VMODE){
    object.id = CAL_ID_VMODE(motor->id);
    object.tx_data = (uint8_t*)&(motor->speed_ref_krpm);
    object.rx_data = (uint8_t*)&(motor->speed_krpm);
  } else if(motor->setting.mode == PMODE){
    object.id = CAL_ID_PMODE(motor->id);
    object.tx_data = (uint8_t*)&(motor->pos_ref_mrev);
    object.rx_data = (uint8_t*)&(motor->pos_mrev);
  }
  object.tx_len = 4;
  object.rx_len = 4;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UDC_Poll_Single(&object);
}

udc_rx_state_e motor_get_status_2016(motor_2016_t *motor){
	UDC_Obj_t object;
  object.id = CAL_ID_M_STATUS(motor->id);
  object.rx_data = (uint8_t*)&(motor->status);
  object.tx_len = 0;
  object.rx_len = 18;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UDC_Poll_Single(&object);
}

udc_rx_state_e motor_send_setting_2016(motor_2016_t *motor){
	UDC_Obj_t object;
  object.id = CAL_ID_M_SETTING(motor->id);
  object.tx_data = (uint8_t*)&(motor->setting);
  object.tx_len = 22;
  object.rx_len = 0;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UDC_Poll_Single(&object);
}

udc_rx_state_e motor_setIdle_2016(motor_2016_t *motor){
	UDC_Obj_t object;
  motor_setting_2016_t setting;
  memcpy(&setting, &(motor->setting), sizeof(motor_setting_t));
  setting.mode = UNLOCK;
  object.id = CAL_ID_M_SETTING(motor->id);
  object.tx_data = (uint8_t*)&setting;
  object.tx_len = 22;
  object.rx_len = 0;
  object.rx_callback = NULL;
  //object.tx_callback = NULL;
  return UDC_Poll_Single(&object);
}

