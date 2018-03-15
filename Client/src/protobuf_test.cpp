#include "../include/test.pb.h"
#include <string>
#include <SFML/System/Vector2.hpp>

void protobufTest(void)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	pb::PlayerBase PBase;
	PBase.set_m_id(1);
	PBase.set_m_name("bbcorp");
	PBase.set_m_health(100);
	PBase.set_m_ammo(20);
	PBase.set_m_orientation(0);
	PBase.set_m_state(0);
	sf::Vector2u Vect(100, 200);
	pb::Vector2u Vect2;
	//pb::Vector2u *Vect = new pb::Vector2u;

	PBase.set_allocated_m_pos((pb::Vector2u) Vect);
	std::string str;
	bool ret;
	ret = PBase.SerializeToString(&str);
	google::protobuf::ShutdownProtobufLibrary();
	//std::cout << ret;
}