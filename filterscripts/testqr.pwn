/*
	----------------------------------------------------------------


		 � ���� ������ ��� ����� ����� ���� �������� ������� �������� �������� QR ��� � ���� � ������� �����������, �� ���� ���� ��������.
	�������� ����������� � ���, ��� � qrcode ���� � ����� ����� ���������� ����� 300 ��������, ��� ����� �� ������ � ������
	����� � ��� ������ �� ��������� �� ��������� ��� ����������.
	��� �������� ����� QRcode ���� �������� �������� � ���� �� ����� � �������� �� ��� ������, ��� �������� � ���,
	��� � ���������� ������� �������� � ����� �����, � ����� ������� qr ��� � ���������� �������� �� ������ ��������.
	� ����� � ������ �� � ������ � ������ ������� �� ������.

		� QR ����� �������� ��������� � ����� SAMP. ������ ������ ��������� ����� ���� ������� � ����� ��������.
		��� �� ����� � MTA ���� ����������� �������� ���� ��������, �� � samp - ���.
	� ������ ������ ������� �������� �������� ����� � �������� ������������� ������� ����� � ���������� ������.

	��� ��� � �������� ���������:
	��������� ��������� ���������� ����� ������ �������;
	�������� �� �������� ������ ��� ������ ����� ����� ������ �� �����;
	������� ������������ ( ���� �� ���� http://web.wathsapp.com/ );
	���������� QR ��� � ������� �� ������;
	� ������ ������!

	�����: vawylon

	a_mysql
	https://github.com/pBlueG/SA-MP-MySQL/releases

	sscanf2
	https://github.com/maddinat0r/sscanf/releases


	----------------------------------------------------------------------
*/






#define QRCODE_HOST "https://chiliadrp.com/qrcode/q.php"
#define QRCODE_LINK "https://chiliadrp.com/qrcode/g.php"

#include <qrcode>


new qrcodes[1248];  // ������ � ������� ����� ������� qr ���

public OnFilterScriptInit()
{
	QRCodeInit("92.119.113.102", "qrcode", "cN0eD8gX1r", "qrcode");  // ������������ � ���� ������
	return 1;
}


CMD:show(playerid, p[])
{
    new handle[64], text[128], type;
    if(sscanf(p, "p<,>s[64]s[128]d", handle, text, type))
	{
		return SendClientMessage(playerid, 0xFF4444FF, "/show [handle], [text], [type]");
	}
	if(QrCodeIsSet(handle) == 0)    // ���� QR ��� �� ����������
	{
	    if(QRCodeSet(type, handle, text) == 0)  // ������ QR ���
		{
		    SendClientMessage(playerid, 0xFF4444FF, "����� ������� �������!"); // ���� ����� ��������, �� �������
			return 1;
		}
		format(text, sizeof(text), "QRCode {FF0000}%s{44FF44} ������, ������� �������� �������", handle);
		SendClientMessage(playerid, 0x44FF44FF, text);
		return 1;
	}
	else // ���� QR ��� ����������
	{
	    if(LoadQRCode(handle, qrcodes)) // ��������� QR ��� � ������ qrcodes
	    {
			CreatePlayerTextDrawsQrCode(playerid, qrcodes, 120.0, 120.0, 0.0); // ���������� QR ���
			SendClientMessage(playerid, 0xFFCC00FF, "�������� ������ ��������� �� QR ���!");
			return 1;
		}
		return SendClientMessage(playerid, 0xFF4444FF, "������ �������� QR ����!");
	}
}

public OnPlayerCloseQrCode(playerid) // ���������� ����� ����� ��������� QR ��� ( ����� ESC ��� ������ CLOSE )
{
	return 1;
}