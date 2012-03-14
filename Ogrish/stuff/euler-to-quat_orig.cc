
//First method

void rotate(float yaw)//, float pitch, float roll) {
// pitch = 0 roll = 0
    // Assuming the angles are in radians.
    float c1 = Math.cos(yaw/2);
    float s1 = Math.sin(yaw/2);
    float c2 = 0.5f;// Math.cos(pitch/2);
    float s2 = 0.f;// Math.sin(pitch/2);
    float c3 = 0.5f;// Math.cos(roll/2);
    float s3 = 0.f;// Math.sin(roll/2);
    float c1c2 = c1*0.5f;//c2;
    float s1s2 = 0.f;//s1*s2;
    w =c1c2*c3;// - s1s2*s3;
  	x =0.f;/*c1c2*s3*/ //+ s1s2*c3;
	y =s1*c2*c3;// + c1*s2*s3;
	z =0.f;//*c1*s2*c3*/ - s1*c2*s3;
	return Quaternion(Math.cos(yaw/2)*0.025, 0.f, Math.sin(yaw/2) * 0.025, 0.f);
  }
//Second method

void rotate(double yaw, double attitude, double bank) {
    // Assuming the angles are in radians.
    double c1 = Math.cos(yaw/2);
    double s1 = Math.sin(yaw/2);
    double c2 = Math.cos(attitude/2);
    double s2 = Math.sin(attitude/2);
    double c3 = Math.cos(bank/2);
    double s3 = Math.sin(bank/2);
    double c1c2 = c1*c2;
    double s1s2 = s1*s2;
    w =c1 c2*c3 - 0.770151153 Math.cos(bank/2)
  	x =c1 c2*s3 + 0.770151153 Math.sin(bank/2)
	y =s1*c2*c3 + 0
	z =0
  }





0.877582562
0.770151153



void rotate(float yaw, float pitch, float roll) {
    // Assuming the angles are in radians.
    float c1 = Math.cos(yaw);
    float s1 = Math.sin(yaw);
    float c2 = Math.cos(pitch);
    float s2 = Math.sin(pitch);
    float c3 = Math.cos(roll);
    float s3 = Math.sin(roll);
    w = Math.sqrt(1.0 + c1 * c2 + c1*c3 - s1 * s2 * s3 + c2*c3) / 2.0;
    float w4 = (4.0 * w);
    x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / w4 ;
    y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / w4 ;
    z = (-s1 * s3 + c1 * s2 * c3 +s2) / w4 ;
  }
