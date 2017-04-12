#pragma once

namespace conf
{
	enum LocalCache
	{
		tag_SessionListCache = 0,
		tag_CataLogListCache
	};

	enum cf_tag_login
	{
		tag_lsrecentlist	= 10,
		tag_lsrecentuid,
		tag_lsisptype,
		tag_lsautologin = 20, 
		tag_cookie, 
		tag_imLoginStatus,
		tag_networkproxy
	};

	enum mysetcfg
	{	//新来的tag一律后插，不然有问题
		tag_basesysinfo = 100,
		tag_talksysinfo,
		tag_talkmouseinfo,
		tag_talkkey,
		tag_session,
		tag_sessionpos,
		tag_talksnd,
		tag_mic_agc,
		tag_mic_enhance,
		tag_sessionulistwidth,
		tag_defaultinputdevice,
		tag_defaultoutputdevice,
		tag_managershow,
		tag_managerheight,
		tag_microphonelistheight,
		tag_messageinputheight,
		tag_bulletinClosedChannels,
		tag_sendmsguserctrladdenter,
		tag_JoinAndLeaveTips,
		tag_privateScreen,
		tag_skin,
		tag_privateChatSound,
		tag_DockWnd,
		tag_ImBaseHotKey,
		tag_ImInfoRemainder,
		tag_input_vol,
		tag_output_vol,
		tag_imSkin,
		tag_showRecentBuddyList,
		tag_showBackList,
		tag_LastPhotoChoose,
		tag_systemSound,
		tag_maxSoundFirst,
		tag_haveCheckSoundCard,
		tag_lastSkin,                        //保留最后一次登陆的皮肤。
		tag_closeSound,					     //关闭所有声音
		tag_forbidInviteToChannel,			 //禁止别人邀请进频道
		tag_kalaokmixkind,					 //使用那种混音模式进行卡拉OK	
		tag_reverbenabled,
		tag_reverbpreset,
		tag_reverbinputvolume1,
		tag_reverbvolume1,
		tag_isshowaliaseidmsg,
		tag_isshowonlinebuddy,     			// 显示在线好友
		tag_shareInfo,						// 分享信息
		tag_soundHotKey,					//声音开关的热键
		tag_showNickAndRemark,				// 显示昵称和备注
		tag_micBoostScale,
		tag_micBoostKind,
		tag_IMMessageNoice,					//IM消息的提醒方式
		tag_micDenoise1,
		tag_audioSafeMode1,
		tag_usePLC1,
		tag_haveAutoSetUsePLC1,
		tag_broadcastReceiverRoler,
		tag_imTransmitFilePath,
		tag_pipstartinfo,					// 0为不启用，1为启用
		tag_micDenoise2,
		tag_audioSafeMode2,
		tag_usePLC2,
		tag_haveAutoSetUsePLC2,
		tag_newgamereport,					//新游戏报告
		tag_setPrivateChatAutoReply,	// 0表示没有启用私聊自动回复，1表示启用
		tag_idxPrivateChat,				// 记录哪一条自动回复
		tag_reverbinputvolume2,
		tag_reverbvolume2,
		tag_micSelectIdx,				//可用的麦克风序号
		tag_stereoMode,					//立体声模式
		tag_lastSkin2,                    //保留最后一次登陆的皮肤(新的实现)。
		tag_imvoice,							// im语音控件设置
		tag_shopnewsText,				//商场的新消息
		tag_clickKalaokBtnOperation,	//点击Kalaok按钮时进行的操作
		tag_playerPath,					//所使用的播放器路径
		tag_haveShowSelectPlayerWnd,	//是否打开过选择播放器窗口
		tag_newAudioDeviceNotifyWays,		//发现音频设备时的操作，0始终显示；1是始终使用新设备，不显示；2是不使用新设备也不显示
		tag_voiceChangeMode,			//变声模式
		tag_toneColor,					//音色
		tag_exquisite,					//柔和开关
		tag_voiceEffectEnable,			//音效开关
		tag_previousinputdevice,
		tag_previousoutputdevice
	};

	enum maintag
	{
		tag_windowrect = 200
	};

	enum cf_tag_session
	{
		tag_smsgfontdef = 300,			//频道窗口的字体
		tag_smsinputvol,
		tag_smsoutputvol,
		tag_smsgfontyychat				//YY聊天窗口的字体
	};

	// 记住上次管理员封人时的动作
	enum cf_tag_ban
	{
		tag_ban_id = 400,
		tag_ban_ip
	};
}
