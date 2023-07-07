/*

*/
#if defined mysql_included
#endif
#include <a_mysql>

#if defined mysql_included
#endif
#include <sscanf2>


#if defined mysql_included
#endif
//#include <a_http>

#if ( !defined QRCODE_MAX_TEXT_SIZE )
	#define QRCODE_MAX_TEXT_SIZE  (2524)
#endif

#if ( !defined QRCODE_HOST )
	#error Please define QRCODE_HOST link to "q.php".
#endif

#if ( !defined QRCODE_LINK )
	#error Please define QRCODE_LINK link to "g.php".
#endif


#define PARSE_ERROR_MAX_SIZE    2
#define PARSE_ERROR_BAD_ARRAY   3
#define MAX_SIZE_HANDLE         64
#define MAX_TEXT_QRCODE         50

new MySQL:sql_qrcode;
new bool:isinit;
new PlayerText:qrCodeText[MAX_PLAYERS][256] = {{PlayerText:INVALID_TEXT_DRAW, ...}, ...};
new bool:isshowqrcode[MAX_PLAYERS];
#define MAX_SIZE_TEXT_QRCODE 256
#define MAX_SIZE_HANDLE_QRCODE 64
#define MAX_SIZE_HREF_QRCODE 24


forward OnPlayerCloseQrCode(playerid);


forward PlayerText:CreatePlayerHeaderTextDraw(playerid,
											Float:x,
											Float:y,
											tdtext[],
											aligm,
											bagcolor,
											font,
											Float:sx,
											Float:sy,
											drcolor,
											outline,
											propor,
											shadow,
											ubox,
											boxcolor,
											Float:tx,
											Float:ty,
											ymodel,
											Float:rmx,
											Float:rmy,
											Float:rmz,
											Float:zoom,	select);
public PlayerText:CreatePlayerHeaderTextDraw(playerid,
											Float:x,
											Float:y,
											tdtext[],
											aligm,
											bagcolor,
											font,
											Float:sx,
											Float:sy,
											drcolor,
											outline,
											propor,
											shadow,
											ubox,
											boxcolor,
											Float:tx,
											Float:ty,
											ymodel,
											Float:rmx,
											Float:rmy,
											Float:rmz,
											Float:zoom,
											select)
{
	new PlayerText:Textdraw0 = CreatePlayerTextDraw(playerid,x, y, tdtext);
	if(aligm != 0 && aligm != 1)
	{
		PlayerTextDrawAlignment(playerid,Textdraw0, aligm);
	}
	PlayerTextDrawBackgroundColor(playerid,Textdraw0, bagcolor);
	PlayerTextDrawFont(playerid,Textdraw0, font);
	PlayerTextDrawLetterSize(playerid,Textdraw0, sx, sy);
	PlayerTextDrawColor(playerid,Textdraw0, drcolor);
	PlayerTextDrawSetOutline(playerid,Textdraw0, outline);
	PlayerTextDrawSetProportional(playerid,Textdraw0, propor);
 	if(outline == 0)
 	{
		PlayerTextDrawSetShadow(playerid,Textdraw0, shadow);
	}
	if(ubox == 1)
	{
		PlayerTextDrawUseBox(playerid,Textdraw0, ubox);
		PlayerTextDrawBoxColor(playerid,Textdraw0, boxcolor);
	}
	PlayerTextDrawTextSize(playerid,Textdraw0, tx, ty);
	if(ymodel > 0)
	{
		PlayerTextDrawSetPreviewModel(playerid, Textdraw0, ymodel);
		PlayerTextDrawSetPreviewRot(playerid, Textdraw0, rmx, rmy, rmz, zoom);
	}
	PlayerTextDrawSetSelectable(playerid,Textdraw0, select);
	return PlayerText:Textdraw0;
}
stock QRCodeInit(SQL_HOST[], SQL_USER[], SQL_PASS[], SQL_DB[])
{
    sql_qrcode = mysql_connect(SQL_HOST, SQL_USER, SQL_PASS, SQL_DB);
    if(mysql_errno() != 0)
	{
	    return 0;
	}
    isinit = true;
    return 1;
}

stock QrCodeIsSet(qrhandle[])
{
	if(isinit == false) return 0;
	new str[256];
	mysql_format(sql_qrcode, str, sizeof(str), "SELECT * FROM `codes` WHERE `handle` = '%e'", qrhandle);
	mysql_query(sql_qrcode, str);
	if(cache_num_rows() > 0) return 1;
	return 0;
}

stock QRCodeSet(type, qrhandle[], textqr[])
{
	if(strlen(QRCODE_LINK) + strlen(qrhandle)+4 > MAX_TEXT_QRCODE) return 0;
	new h[MAX_SIZE_HANDLE_QRCODE*4];
	strcat( h, qrhandle);
	new u[MAX_SIZE_HREF_QRCODE * 4];
	strcat( u, QRCODE_LINK);
	new q[MAX_SIZE_TEXT_QRCODE * 4];
	strcat( q, textqr);
	ASCII_encode( h, sizeof(h));
	ASCII_encode( q, sizeof(q));
	ASCII_encode( u, sizeof(u));
    if(isinit == false) return 0;
    new POST[sizeof(h)+sizeof(u)+sizeof(q)];
    format(POST, sizeof(POST), "u=%s&t=%d&h=%s&q=%s", u, type, h, q);

	HTTP(5001, HTTP_POST, QRCODE_HOST, POST, "QrCodeReturn");
	return 1;
}

forward QrCodeReturn( iIndex, iResponseCode, const szData[ ] );
public  QrCodeReturn( iIndex, iResponseCode, const szData[ ] )
{
	if(iIndex == 5001)
	{
		if ( szData[ 0 ] ) print(szData);
	}
}

stock LoadQRCode(qrhandle[], qrcode[], sizeqrcode = sizeof(qrcode))
{
    if(isinit == false) return 0;
	for(new i; i<sizeqrcode; i++)
	{
		    qrcode[i] = EOS;
	}
	new str[256], string[1824];
    mysql_format(sql_qrcode, str, sizeof(str), "SELECT `qrcode` FROM `codes` WHERE `handle` = '%e'", qrhandle);
	new Cache:res = mysql_query(sql_qrcode, str);
	if(cache_num_rows() > 0)
	{
		cache_get_value_index(0, 0, string, sizeof(string));
		cache_delete(res);
		return ParseString(string, qrcode);
	}
	cache_delete(res);
	return 0;
}

stock GetTypeForHandle(qrhandle[])
{
    if(isinit == false) return 0;
	new str[256], type;
    mysql_format(sql_qrcode, str, sizeof(str), "SELECT `type` FROM `codes` WHERE `handle` = '%e'", qrhandle);
	new Cache:res = mysql_query(sql_qrcode, str);
	if(cache_num_rows() > 0)
	{
		cache_get_value_index_int(0, 0, type);
		cache_delete(res);
		return type;
	}
	cache_delete(res);
	return 0;
}


stock ParseString(stringqr[], qrcode[])
{
		new textdraws;
        if(isinit == false) return 0;
        if(!sscanf(stringqr, "p<|>a<i>[700]", qrcode)) return PARSE_ERROR_BAD_ARRAY;
		for(new i; i<strlen(qrcode); i+=3) if(qrcode[i] != 0) textdraws ++;
		if(textdraws > 256*3)
		{
			return PARSE_ERROR_MAX_SIZE;
		}
		return 1;
}

new textcount;
stock CreatePlayerTextDrawsQrCode(playerid, qrcode[], Float:x, Float: y, Float: size, sizeqr = sizeof(qrcode))
{

        if(isinit == false) return 0;
		new Float: fsize =0.019999+(0.58*size), t;
		new Float:sizexy = 0.4 + 0.6*size;
		new Float:sizex;
		new Float:sizey;
		new Float:sizecy;
		new sizecx;
		DestroyPlayerTextDrawsQrCode(playerid);
        qrCodeText[playerid][sizeof(qrCodeText[])-1] = CreatePlayerHeaderTextDraw(playerid, x-15.0, y-15.0, "_", 2, -1, 5, 0.619999, 11.199996, -1, 0, 1, 1, 1, 0, 103.000000, 106.000000, 327, -16.000000, 0.000000, -55.000000, 999.000000, 0);
		for(new i; i<sizeqr; i += 3)
	    {
	        if(qrcode[i] != 0 )
	        {
	            textcount ++;
	            qrCodeText[playerid][t] = CreatePlayerHeaderTextDraw(playerid, x+(10.0*sizexy)*qrcode[i+2], y+(10.0*sizexy)*qrcode[i+1], "_", 1, 255, 1, 0.000000, fsize , -1, 0, 1, 1, 1, 255, (x+qrcode[i+2]*(10.0*sizexy) + qrcode[i]*(10.0*sizexy))-(1.6/sizexy), 23.000000, -1, -16.000000, 0.000000, -55.000000, 1.000000, 0);
				if(sizecx < qrcode[i+2] )
				{
					sizex = (qrcode[i+2]*(10.0*sizexy) + qrcode[i]*(10.0*sizexy))-(1.6/sizexy);
					sizecx =qrcode[i+2];
				}
				if(sizecy < y+(10.0*sizexy)*qrcode[i+1])
				{
					sizecy = y+(10.0*sizexy)*qrcode[i+1];
				}
				if(sizey < (10.0*sizexy)*qrcode[i+1]) sizey= qrcode[i+1];
				t ++;
         	}
	    }
        qrCodeText[playerid][sizeof(qrCodeText[])-2] = CreatePlayerHeaderTextDraw(playerid, x+(sizex/2.0), sizecy+10.0, "Point your smartphone's camera at the QRcode.", 2, 255, 1, 0.230000, 1.299999, -1, 1, 1, 1, 1, -1, 89.000000, 105.000000, -1, -16.000000, 0.000000, -55.000000, 1.000000, 0);
        qrCodeText[playerid][sizeof(qrCodeText[])-3] = CreatePlayerHeaderTextDraw(playerid, x+11.0, y-16.0, "Close", 2, 255, 1, 0.230000, 1.299998, -1, 1, 1, 1, 1, -1, 15.000000, 48.000000, -1, -16.000000, 0.000000, -55.000000, 1.000000, 1);

	    PlayerTextDrawTextSize(playerid,qrCodeText[playerid][sizeof(qrCodeText[])-1],sizex+30.0/**((209.0-82.0)/127.0)*/, (sizexy*10.0*(sizey+1))+50.0);//210.0, 209.0);//(10.0*sizexy)*sizex, 100.0+2(10.0*sizexy)*sizey);
     	
     	
     	PlayerTextDrawShow(playerid, qrCodeText[playerid][sizeof(qrCodeText[])-1]);
		PlayerTextDrawShow(playerid, qrCodeText[playerid][sizeof(qrCodeText[])-2]);
		PlayerTextDrawShow(playerid, qrCodeText[playerid][sizeof(qrCodeText[])-3]);
	    isshowqrcode[playerid] = true;
		for(new i; i<sizeof(qrCodeText[])-3; i++)
		{
		    if(qrCodeText[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		    {
	    		PlayerTextDrawShow(playerid, qrCodeText[playerid][i]);
			}
		}
		SelectTextDraw(playerid, 0xFF0000FF);
		return 1;
}



stock DestroyPlayerTextDrawsQrCode(playerid)
{
    if(isshowqrcode[playerid] == true)
	{
	    PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		CancelSelectTextDraw(playerid);
		if(funcidx("OnPlayerCloseQrCode") == -1) return 1;
		OnPlayerCloseQrCode(playerid);
	}
    isshowqrcode[playerid] = false;
	for(new i; i<sizeof(qrCodeText[]); i++)
	{
	    if(qrCodeText[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
	    {
	        textcount --;
    		PlayerTextDrawDestroy(playerid, qrCodeText[playerid][i]);
    		qrCodeText[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	return 1;
}
stock ASCII_encode( szString[ ], iSize = sizeof( szString ) )
{
	for ( new i = 0, l = strlen( szString ); i < l; i++ )
	{
		switch ( szString[ i ] )
		{
			case '!', '(', ')', '\'', '*',
			     '0' .. '9',
			     'A' .. 'Z',
			     'a' .. 'z':
			{
				continue;
			}

			case ' ':
			{
				szString[ i ] = '+';

				continue;
			}
		}

		new
			s_szHex[ 8 ]
		;

		if ( i + 3 >= iSize )
		{
			szString[ i ] = EOS;

			break;
		}

		if ( l + 3 >= iSize )
			szString[ iSize - 3 ] = EOS;

		format( s_szHex, sizeof( s_szHex ), "%02h", szString[ i ] );

		szString[ i ] = '%';

		strins( szString, s_szHex, i + 1, iSize );

		l += 2;
		i += 2;

		if ( l > iSize - 1 )
			l = iSize - 1;
	}
}


public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(isshowqrcode[playerid])
	{
	    if(clickedid == Text:INVALID_TEXT_DRAW)
	    {
	        DestroyPlayerTextDrawsQrCode(playerid);
	        return 1;
        }
    }
	#if defined ad_OnPlayerClickTextDraw
		return ad_OnPlayerClickTextDraw(playerid, clickedid);
	#else
	    return OnPlayerClickTextDraw(playerid, clickedid);
	#endif
}

#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw ad_OnPlayerClickTextDraw
#if defined ad_OnPlayerClickTextDraw
	forward ad_OnPlayerClickTextDraw(playerid, Text:clickedid);
#endif


public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(isshowqrcode[playerid])
	{
	    if(playertextid == PlayerText:INVALID_TEXT_DRAW || playertextid == qrCodeText[playerid][sizeof(qrCodeText[])-3])
	    {
	        DestroyPlayerTextDrawsQrCode(playerid);
	        return 1;
	    }
	}
	#if defined ad_OnPlayerClickPlayerTextDraw
		return ad_OnPlayerClickPlayerTextDraw(playerid, playertextid);
	#else
	    return OnPlayerClickPlayerTextDraw(playerid, playertextid);
	#endif
}

#if defined _ALS_OnPlayer\
	ClickPlayerTextDraw
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTextDraw
#endif
#define OnPlayerClickPlayerTextDraw ad_OnPlayerClickPlayerTextDraw
#if defined ad_OnPlayerClickPlayerTextDraw
	forward ad_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid);
#endif
