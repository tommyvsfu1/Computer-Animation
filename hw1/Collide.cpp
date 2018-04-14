void CMassSpringSystem::BallNetCollision()
{
    static const double eEPSILON = 0.01;
	//TO DO 2
	for (int i = 0; i < this->BallNum(); i++) {
		std::vector<Vector3d> buffer;
		for (int k = 0; k < this->m_GoalNet.ParticleNum(); k++) {
			
				Vector3d PosVector = (m_GoalNet.GetParticle(k).GetPosition() - m_Balls[i].GetPosition());
				double length = sqrt(PosVector.x*PosVector.x + PosVector.y*PosVector.y + PosVector.z * PosVector.z);

				Vector3d stopVector = m_Balls[i].GetVelocity();
				double len = sqrt(stopVector.x*stopVector.x + stopVector.y*stopVector.y + stopVector.z*stopVector.z);
				if ( (length - m_Balls[i].GetRadius())  < eEPSILON) {

					/* If the ball is hit to the Net upper boundary then reflect 
					   No set to the boundary except the highest particles.
					*/
					if (m_GoalNet.GetParticle(k).GetPosition().y == 2.5) { // 2.5 is the Net Height
						PosVector.x = PosVector.x / length;
						PosVector.y = PosVector.y / length;
						PosVector.z = PosVector.z / length;
						m_Balls[i].SetForce(- m_Balls[i].GetForce());
						m_Balls[i].SetVelocity(-m_Balls[i].GetVelocity());
						break;
					}
					PosVector.x = PosVector.x / length;
					PosVector.y = PosVector.y / length;
					PosVector.z = PosVector.z / length;
					//std::cout << m_Balls[i].GetVelocity().Length() << std::endl;
					//Vector3d v1n = PosVector*(m_Balls[i].GetVelocity().Length() * cos(m_Balls[i].GetVelocity().AngleBetween(PosVector)));
					Vector3d v1n = PosVector * ( ( m_Balls[i].GetVelocity().DotProduct(PosVector) ) );
					Vector3d v1t = m_Balls[i].GetVelocity() - v1n;
					//Vector3d v2n = -PosVector*(m_GoalNet.GetParticle(k).GetVelocity().Length() *cos(m_GoalNet.GetParticle(k).GetVelocity().AngleBetween(-PosVector)));
					Vector3d v2n = -PosVector * ( m_GoalNet.GetParticle(k).GetVelocity().DotProduct(-PosVector) );
					Vector3d v2t = m_GoalNet.GetParticle(k).GetVelocity() -v2n;

					//if (v1n.DotProduct(v2n) < 0) { 	}
					/* Caution :: Collision occurs both on same direction velocity or negative velocity !!! So Don't need condition 
					   --                          --
					-      -    ----->  v1      -      -   ----> v2
					-      -                    -      -
					   --                          --

					       
					   --                                       --
					-      -    ----->  v1       <----- v2   -      -   
					-      -                                 -      -
					   --                                       --
					   IF YOU USE CONDTION WILL CAUSE BALL "PENETRATE" THE PARTICLE
					*/
 
					double m1 = m_Balls[i].GetMass();
					double m2 = m_GoalNet.GetParticle(k).GetMass();
					Vector3d v1_ = (( (v1n*(m1 - m2)) + (2 * m2*v2n) ) / (m1 + m2)) + v1t;
					Vector3d v2_ = (( (v2n*(m2 - m1)) + (2 * m1*v1n) ) / (m1 + m2)) + v2t;
					buffer.push_back(v1_);
					//std::cout << "v1 is:" << v1_ << std::endl;
					//std::cout << "v2 is:" << v2_ << std::endl;
					m_GoalNet.GetParticle(k).SetVelocity(v2_);


				}
			}

		/* For Multi-collision , use average velocity to approximate it.*/
		if (buffer.size() > 0) {  
			//std::cout << "Buffer size is:" << buffer.size() << std::endl;
			Vector3d average(0, 0, 0);
			for (int idx = 0; idx < buffer.size(); idx++) {
				average += buffer[idx];
			}
			average.x = average.x / buffer.size();
			average.y = average.y / buffer.size();
			average.z = average.z / buffer.size();
			m_Balls[i].SetVelocity(average);
		}

	}
}