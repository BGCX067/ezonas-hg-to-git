// Build a matrix from a quaternion
// QUAT -> (-) -> MAT
D3DXMATRIX* WINAPI D3DXMatrixRotationQuaternion
    (D3DXMATRIX *pOut, CONST D3DXQUATERNION *pQ);

// MAT -> (-) -> QUAT
// Build a quaternion from a rotation matrix.
D3DXQUATERNION* WINAPI D3DXQuaternionRotationMatrix
    (D3DXQUATERNION *pOut, CONST D3DXMATRIX *pM);
//---
// Rotation about arbitrary axis.
D3DXQUATERNION* WINAPI D3DXQuaternionRotationAxis
    (D3DXQUATERNION *pOut, CONST D3DXVECTOR3 *pV, FLOAT Angle);
	
	
// Quaternion multiplication.  The result represents the rotation Q2
// followed by the rotation Q1.  (Out = Q2 * Q1)
D3DXQUATERNION* WINAPI D3DXQuaternionMultiply
    ( D3DXQUATERNION *pOut, CONST D3DXQUATERNION *pQ1,
      CONST D3DXQUATERNION *pQ2 );      
// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
// Expects unit quaternions.
D3DXQUATERNION* WINAPI D3DXQuaternionSlerp
    ( D3DXQUATERNION *pOut, CONST D3DXQUATERNION *pQ1,
      CONST D3DXQUATERNION *pQ2, FLOAT t );