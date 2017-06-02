/*
 * test_code.c
 *
 *  Created on: 2016¦~6¤ë15¤é
 *      Author: Hung
 */

bool up_slope() {
  x_position_ready = 0;
  stage1_line_flag_x = 0;
  line_x_d = 0;

  if(LineSensor[2].Position[1] > LINE_NARROW && LineSensor[2].Position[1] < LINE_THICK && LineSensor[2].Position[3] < 0){
    if(LineSensor[2].Position[0] > 15 && LineSensor[2].Position[0] < 205){
      line_x_d -= LineSensor[2].Position[0] - 110;
      x_position_ready ++;
    }
  }

  if(LineSensor[3].Position[1] > LINE_NARROW && LineSensor[3].Position[1] < LINE_THICK && LineSensor[3].Position[3] < 0){
    if(LineSensor[3].Position[0] > 15 && LineSensor[3].Position[0] < 205){
      if(line_x_d == 0){
        line_x_d += LineSensor[3].Position[0] - 110;
      }else{
        line_x_d += LineSensor[3].Position[0] - 110;
        line_x_d /= 2;
      }
      x_position_ready ++;
    }
  }

  if(y > -300 && y < 300 && x > -300 && x < 300 && x_position_ready == 2){
    xf = 0 + 268*(1-cosf(HeadingAngle)) + line_x_d;
  }else if(y > -300 && y < 300 && x > blue_path1[0][0] - 300 && x < blue_path1[0][0] + 300 && x_position_ready == 2){
    xf = blue_path1[0][0] + 268*(1-cosf(HeadingAngle)) + line_x_d;
  }else if(y > blue_path1[7][1] - 300 && y < blue_path1[7][1] + 300 && check_point[1] && x_position_ready == 2){
    xf = blue_path1[7][0] + 268*(1-cosf(HeadingAngle)) + line_x_d;
  }else if(y > blue_path1[11][1] - 300 && y < red_path1[11][1] + 300 && x > -300 && x < 300 && x_position_ready == 2){
    xf = 0 + 268*(1-cosf(HeadingAngle)) - line_x_d;
  }else if(y > blue_path1[11][1] - 300 && y < blue_path1[11][1] + 300 && x > blue_path1[11][0] -1000 && x < blue_path1[11][0] + 1000 && x_position_ready == 2){
    xf = blue_path1[11][0] + 268*(1-cosf(HeadingAngle)) - line_x_d;
  }

}
