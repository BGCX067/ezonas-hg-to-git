	//n_recoil->setOrientation(Math::Cos(recoil_pitch*.5f) * .770151153f, 0, 0,
	//	Math::Sin(recoil_pitch*.5f) * .770151153f); // <-- this is a set roll
	//	(Math::Cos(recoil_yaw/2) * 0.025f, 0.f,
	//	Math::Sin(recoil_yaw/2) * 0.025f, 0.f); // <--- this set yaw (I think)



/*
First method

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
    w =c1c2*c3 - s1s2*s3;
  	x =c1c2*s3 + s1s2*c3;
	y =s1*c2*c3 + c1*s2*s3;
	z =c1*s2*c3 - s1*c2*s3;
  }
Second method

void rotate(double yaw, double attitude, double bank) {
    // Assuming the angles are in radians.
    double c1 = Math.cos(yaw);
    double s1 = Math.sin(yaw);
    double c2 = Math.cos(attitude);
    double s2 = Math.sin(attitude);
    double c3 = Math.cos(bank);
    double s3 = Math.sin(bank);
    w = Math.sqrt(1.0 + c1 * c2 + c1*c3 - s1 * s2 * s3 + c2*c3) / 2.0;
    double w4 = (4.0 * w);
    x = (c2 * s3 + c1 * s3 + s1 * s2 * c3) / w4 ;
    y = (s1 * c2 + s1 * c3 + c1 * s2 * s3) / w4 ;
    z = (-s1 * s3 + c1 * s2 * c3 +s2) / w4 ;
  }
Deri
*/