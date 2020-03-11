#define Kp  0.02// 0.1//0.03
#define Kd  0.11//0.5 kalibrasyonda 0.3 iyi değer kalibre yoksa 0.5 iyi
#define Ki  0.0001//0.0001

/*motor settings*/
///////////////////////////////////////
#define max_speed 255
#define min_speed -255
#define base_speed 130

#define base_speed_s1 50 
#define base_speed_s2 70 
#define base_speed_s3 90 

#define base_speed_f1 180 
#define base_speed_f2 200 

#define corner_speed 50
///////////////////////////////////////

/*drone motor settings*/
///////////////////////////////////////
#define drone_max_speed 170
#define drone_base_speed 80
#define drone_min_speed 0
///////////////////////////////////////

#define wheel_factor 1 //k=10.6 k/2=5.3

#define change_left_error -750
#define change_right_error 750

#define choose_left_error -2500
#define choose_right_error 2500