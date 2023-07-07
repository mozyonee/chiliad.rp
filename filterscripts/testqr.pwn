/*
	----------------------------------------------------------------


		 В моей голове уже давно лежит идея инклуйда который позволит рисовать QR код в игре с помощью текстдравов, но была одна проблема.
	Проблема заключалась в том, что в qrcode даже в самом малом содержится около 300 пикселей, что никак не входит в лимиты
	сампа и так просто не получится по пиксельно его нарисовать.
	Мне пришлось сжать QRcode путём парсинга пикселей с лево на право и записать их как строку, ещё хитрость в том,
	что я посчитывал сколько пикселей в одной линии, а когда рисовал qr код я растягивал тексдрав на ширину пикселей.
	В общем я сложил всё в голове и принял решение всё выйдет.

		У QR кодов огромный потенциал в сфере SAMP. Данный иклуйд разрушает стену межу игроком и окном браузера.
		Как мы знаем в MTA есть возможность показать окно браузера, но в samp - нет.
	Я считаю данный инклуйд частично разрушит стену и позволит разработчикам открыть двери в разработки систем.

	Вот как я оцениваю потенциал:
	Упрощение процедуры заполнения формы сборов средств;
	Редирект на страницу оплаты или полный отказ формы доната на сайте;
	Система безопасности ( вход по типу http://web.wathsapp.com/ );
	Показывать QR код с ссылкой на ресурс;
	И многое другое!

	Автор: vawylon

	a_mysql
	https://github.com/pBlueG/SA-MP-MySQL/releases

	sscanf2
	https://github.com/maddinat0r/sscanf/releases


	----------------------------------------------------------------------
*/






#define QRCODE_HOST "https://chiliadrp.com/qrcode/q.php"
#define QRCODE_LINK "https://chiliadrp.com/qrcode/g.php"

#include <qrcode>


new qrcodes[1248];  // массив в котором будем хранить qr код

public OnFilterScriptInit()
{
	QRCodeInit("92.119.113.102", "qrcode", "cN0eD8gX1r", "qrcode");  // подключаемся к базе данных
	return 1;
}


CMD:show(playerid, p[])
{
    new handle[64], text[128], type;
    if(sscanf(p, "p<,>s[64]s[128]d", handle, text, type))
	{
		return SendClientMessage(playerid, 0xFF4444FF, "/show [handle], [text], [type]");
	}
	if(QrCodeIsSet(handle) == 0)    // если QR код не существует
	{
	    if(QRCodeSet(type, handle, text) == 0)  // создаём QR код
		{
		    SendClientMessage(playerid, 0xFF4444FF, "Текст слишком большой!"); // если текст огромный, то выводим
			return 1;
		}
		format(text, sizeof(text), "QRCode {FF0000}%s{44FF44} создан, введите повторно команду", handle);
		SendClientMessage(playerid, 0x44FF44FF, text);
		return 1;
	}
	else // если QR код существует
	{
	    if(LoadQRCode(handle, qrcodes)) // загружаем QR код в массив qrcodes
	    {
			CreatePlayerTextDrawsQrCode(playerid, qrcodes, 120.0, 120.0, 0.0); // показываем QR код
			SendClientMessage(playerid, 0xFFCC00FF, "Наведите камеру смартфона на QR код!");
			return 1;
		}
		return SendClientMessage(playerid, 0xFF4444FF, "Ошибка загрузки QR кода!");
	}
}

public OnPlayerCloseQrCode(playerid) // вызывается когда игрок закрывает QR код ( нажал ESC или кнопку CLOSE )
{
	return 1;
}