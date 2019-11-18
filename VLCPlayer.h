#pragma once

#include <Windows.h>

#include<iostream>
#include <vlc/vlc.h>

namespace VLC
{

	class Player
	{
	public:
		Player();
		~Player();
		void InitPlayer();
		bool StartPlayer(HWND hwnd);

	private:
		libvlc_media_t* vlc_media;
		libvlc_media_player_t* vlc_player;
		libvlc_instance_t* vlc_instance;
	};


};

