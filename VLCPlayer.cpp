#include "VLCPlayer.h"

VLC::Player::Player()
{
	VLC::Player::vlc_instance = NULL;
	VLC::Player::vlc_media = NULL;
	VLC::Player::vlc_player = NULL;
}

VLC::Player::~Player()
{


}

bool VLC::Player::StartPlayer(HWND hwnd)
{
	if (vlc_instance==NULL)
	{
		return false;
	}

	vlc_media=libvlc_media_new_path(vlc_instance,"D:\\12.mp4");

	if (vlc_media==NULL)
	{
		return false;
	}
	libvlc_media_parse(vlc_media);

	vlc_player = libvlc_media_player_new_from_media(vlc_media);

	libvlc_media_player_set_hwnd(vlc_player, hwnd);

	libvlc_media_player_play(vlc_player);
}

void VLC::Player::InitPlayer()
{
  vlc_instance=	libvlc_new(0,NULL);
  if (vlc_instance==NULL)
  {
	  MessageBoxA(0,"初始化失败","枫叶提示",0);
  }
}