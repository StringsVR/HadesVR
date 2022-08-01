#include "dataHandler.h"

void CdataHandler::CalcIMUVelocity(_ControllerData& _data) 
{
	//get deltatime
	auto now = std::chrono::high_resolution_clock::now();
	deltatime = std::chrono::duration_cast<std::chrono::microseconds>(now - _data.lastUpdate).count() / 1000000.0f;
	_data.lastUpdate = now;

	//Rotate gravity vector https://web.archive.org/web/20121004000626/http://www.varesano.net/blog/fabio/simple-gravity-compensation-9-dom-imus
	Vector3 g = Vector3(-(2.0f * (_data.Rotation.X * _data.Rotation.W - _data.Rotation.Y * _data.Rotation.Z)),
						(2.0f * (_data.Rotation.Y * _data.Rotation.X + _data.Rotation.Z * _data.Rotation.W)),
						(_data.Rotation.Y * _data.Rotation.Y - _data.Rotation.X * _data.Rotation.X - _data.Rotation.Z * _data.Rotation.Z + _data.Rotation.W * _data.Rotation.W));

	//remove gravity vector (or at least attempt to)
	Vector3 lin_Acc = _data.Accel - g;

	//convert to m/s^2
	lin_Acc *= 9.80665f;

	//integrate to get velocity													
	_data.Velocity += (lin_Acc * deltatime);

	//decay
	_data.Velocity *= 0.99f;

	//update old velocity
	_data.oldVelocity = _data.Velocity;
}

void CdataHandler::CalcIMUVelocity(_HMDData& _data) 
{
	//get deltatime
	auto now = std::chrono::high_resolution_clock::now();
	deltatime = std::chrono::duration_cast<std::chrono::microseconds>(now - _data.lastUpdate).count() / 1000000.0f;
	_data.lastUpdate = now;

	//Rotate gravity vector https://web.archive.org/web/20121004000626/http://www.varesano.net/blog/fabio/simple-gravity-compensation-9-dom-imus
	Vector3 g = Vector3(-(2.0f * (_data.Rotation.X * _data.Rotation.W - _data.Rotation.Y * _data.Rotation.Z)),
						(2.0f * (_data.Rotation.Y * _data.Rotation.X + _data.Rotation.Z * _data.Rotation.W)),
						(_data.Rotation.Y * _data.Rotation.Y - _data.Rotation.X * _data.Rotation.X - _data.Rotation.Z * _data.Rotation.Z + _data.Rotation.W * _data.Rotation.W));

	//remove gravity vector (or at least attempt to)
	Vector3 lin_Acc = _data.Accel - g;

	//convert to m/s^2
	lin_Acc *= 9.80665f;

	//integrate to get velocity													
	_data.Velocity += (lin_Acc * deltatime);

	//decay
	_data.Velocity *= 0.99f;

	//update old velocity
	_data.oldVelocity = _data.Velocity;
}

/*
void CdataHandler::CalcAccelPosition(float quatW, float quatX, float quatY, float quatZ, float accelX, float accelY, float accelZ, PosData& pos) {

	//get time delta
	auto now = std::chrono::high_resolution_clock::now();
	deltatime = std::chrono::duration_cast<std::chrono::microseconds>(now - pos.lastUpdate).count() / 1000000.0f;
	pos.lastUpdate = now;

	//Rotate gravity vector https://web.archive.org/web/20121004000626/http://www.varesano.net/blog/fabio/simple-gravity-compensation-9-dom-imus
	float gx = (2.0f * (quatX * quatZ - quatW * quatY));
	float gy = (2.0f * (quatW * quatX + quatY * quatZ));
	float gz = (quatW * quatW - quatX * quatX - quatY * quatY + quatZ * quatZ);

	float lin_ax = accelX - gx;
	float lin_ay = accelY - gy;
	float lin_az = accelZ - gz;

	//convert to m/s^2
	lin_ax *= 9.80665f;
	lin_ay *= 9.80665f;
	lin_az *= 9.80665f;

	//integrate to get velocity														TODO: REWORK ALL THIS CRAP
	pos.vx += (lin_ay * deltatime);
	pos.vy += (lin_ax * deltatime);
	pos.vz += (lin_az * deltatime);

	//integrate to get position
	pos.posX = ((pos.vx + pos.oldvX) * 0.5f) * deltatime + pos.oldPosX;
	pos.posY = ((pos.vy + pos.oldvY) * 0.5f) * deltatime + pos.oldPosY;
	pos.posZ = ((pos.vz + pos.oldvZ) * 0.5f) * deltatime + pos.oldPosZ;

	//decay
	pos.vx *= 0.8f;
	pos.vy *= 0.8f;
	pos.vz *= 0.8f;

	pos.oldvX = pos.vx;
	pos.oldvY = pos.vy;
	pos.oldvZ = pos.vz;

	pos.oldPosX = pos.posX;
	pos.oldPosY = pos.posY;
	pos.oldPosZ = pos.posZ;
}
*/