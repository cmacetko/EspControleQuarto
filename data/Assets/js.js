function date(format, timestamp) {
    //  discuss at: http://phpjs.org/functions/date/
    // original by: Carlos R. L. Rodrigues (http://www.jsfromhell.com)
    // original by: gettimeofday
    //    parts by: Peter-Paul Koch (http://www.quirksmode.org/js/beat.html)
    // improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // improved by: MeEtc (http://yass.meetcweb.com)
    // improved by: Brad Touesnard
    // improved by: Tim Wiel
    // improved by: Bryan Elliott
    // improved by: David Randall
    // improved by: Theriault
    // improved by: Theriault
    // improved by: Brett Zamir (http://brett-zamir.me)
    // improved by: Theriault
    // improved by: Thomas Beaucourt (http://www.webapp.fr)
    // improved by: JT
    // improved by: Theriault
    // improved by: Rafał Kukawski (http://blog.kukawski.pl)
    // improved by: Theriault
    //    input by: Brett Zamir (http://brett-zamir.me)
    //    input by: majak
    //    input by: Alex
    //    input by: Martin
    //    input by: Alex Wilson
    //    input by: Haravikk
    // bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // bugfixed by: majak
    // bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // bugfixed by: Brett Zamir (http://brett-zamir.me)
    // bugfixed by: omid (http://phpjs.org/functions/380:380#comment_137122)
    // bugfixed by: Chris (http://www.devotis.nl/)
    //        note: Uses global: php_js to store the default timezone
    //        note: Although the function potentially allows timezone info (see notes), it currently does not set
    //        note: per a timezone specified by date_default_timezone_set(). Implementers might use
    //        note: this.php_js.currentTimezoneOffset and this.php_js.currentTimezoneDST set by that function
    //        note: in order to adjust the dates in this function (or our other date functions!) accordingly
    //   example 1: date('H:m:s \\m \\i\\s \\m\\o\\n\\t\\h', 1062402400);
    //   returns 1: '09:09:40 m is month'
    //   example 2: date('F j, Y, g:i a', 1062462400);
    //   returns 2: 'September 2, 2003, 2:26 am'
    //   example 3: date('Y W o', 1062462400);
    //   returns 3: '2003 36 2003'
    //   example 4: x = date('Y m d', (new Date()).getTime()/1000);
    //   example 4: (x+'').length == 10 // 2009 01 09
    //   returns 4: true
    //   example 5: date('W', 1104534000);
    //   returns 5: '53'
    //   example 6: date('B t', 1104534000);
    //   returns 6: '999 31'
    //   example 7: date('W U', 1293750000.82); // 2010-12-31
    //   returns 7: '52 1293750000'
    //   example 8: date('W', 1293836400); // 2011-01-01
    //   returns 8: '52'
    //   example 9: date('W Y-m-d', 1293974054); // 2011-01-02
    //   returns 9: '52 2011-01-02'
  
    var that = this;
    var jsdate, f;
    // Keep this here (works, but for code commented-out below for file size reasons)
    // var tal= [];
    var txt_words = [
      'Sun', 'Mon', 'Tues', 'Wednes', 'Thurs', 'Fri', 'Satur',
      'January', 'February', 'March', 'April', 'May', 'June',
      'July', 'August', 'September', 'October', 'November', 'December'
    ];
    // trailing backslash -> (dropped)
    // a backslash followed by any character (including backslash) -> the character
    // empty string -> empty string
    var formatChr = /\\?(.?)/gi;
    var formatChrCb = function(t, s) {
      return f[t] ? f[t]() : s;
    };
    var _pad = function(n, c) {
      n = String(n);
      while (n.length < c) {
        n = '0' + n;
      }
      return n;
    };
    f = {
      // Day
      d: function() { // Day of month w/leading 0; 01..31
        return _pad(f.j(), 2);
      },
      D: function() { // Shorthand day name; Mon...Sun
        return f.l()
          .slice(0, 3);
      },
      j: function() { // Day of month; 1..31
        return jsdate.getDate();
      },
      l: function() { // Full day name; Monday...Sunday
        return txt_words[f.w()] + 'day';
      },
      N: function() { // ISO-8601 day of week; 1[Mon]..7[Sun]
        return f.w() || 7;
      },
      S: function() { // Ordinal suffix for day of month; st, nd, rd, th
        var j = f.j();
        var i = j % 10;
        if (i <= 3 && parseInt((j % 100) / 10, 10) == 1) {
          i = 0;
        }
        return ['st', 'nd', 'rd'][i - 1] || 'th';
      },
      w: function() { // Day of week; 0[Sun]..6[Sat]
        return jsdate.getDay();
      },
      z: function() { // Day of year; 0..365
        var a = new Date(f.Y(), f.n() - 1, f.j());
        var b = new Date(f.Y(), 0, 1);
        return Math.round((a - b) / 864e5);
      },
  
      // Week
      W: function() { // ISO-8601 week number
        var a = new Date(f.Y(), f.n() - 1, f.j() - f.N() + 3);
        var b = new Date(a.getFullYear(), 0, 4);
        return _pad(1 + Math.round((a - b) / 864e5 / 7), 2);
      },
  
      // Month
      F: function() { // Full month name; January...December
        return txt_words[6 + f.n()];
      },
      m: function() { // Month w/leading 0; 01...12
        return _pad(f.n(), 2);
      },
      M: function() { // Shorthand month name; Jan...Dec
        return f.F()
          .slice(0, 3);
      },
      n: function() { // Month; 1...12
        return jsdate.getMonth() + 1;
      },
      t: function() { // Days in month; 28...31
        return (new Date(f.Y(), f.n(), 0))
          .getDate();
      },
  
      // Year
      L: function() { // Is leap year?; 0 or 1
        var j = f.Y();
        return j % 4 === 0 & j % 100 !== 0 | j % 400 === 0;
      },
      o: function() { // ISO-8601 year
        var n = f.n();
        var W = f.W();
        var Y = f.Y();
        return Y + (n === 12 && W < 9 ? 1 : n === 1 && W > 9 ? -1 : 0);
      },
      Y: function() { // Full year; e.g. 1980...2010
        return jsdate.getFullYear();
      },
      y: function() { // Last two digits of year; 00...99
        return f.Y()
          .toString()
          .slice(-2);
      },
  
      // Time
      a: function() { // am or pm
        return jsdate.getHours() > 11 ? 'pm' : 'am';
      },
      A: function() { // AM or PM
        return f.a()
          .toUpperCase();
      },
      B: function() { // Swatch Internet time; 000..999
        var H = jsdate.getUTCHours() * 36e2;
        // Hours
        var i = jsdate.getUTCMinutes() * 60;
        // Minutes
        var s = jsdate.getUTCSeconds(); // Seconds
        return _pad(Math.floor((H + i + s + 36e2) / 86.4) % 1e3, 3);
      },
      g: function() { // 12-Hours; 1..12
        return f.G() % 12 || 12;
      },
      G: function() { // 24-Hours; 0..23
        return jsdate.getHours();
      },
      h: function() { // 12-Hours w/leading 0; 01..12
        return _pad(f.g(), 2);
      },
      H: function() { // 24-Hours w/leading 0; 00..23
        return _pad(f.G(), 2);
      },
      i: function() { // Minutes w/leading 0; 00..59
        return _pad(jsdate.getMinutes(), 2);
      },
      s: function() { // Seconds w/leading 0; 00..59
        return _pad(jsdate.getSeconds(), 2);
      },
      u: function() { // Microseconds; 000000-999000
        return _pad(jsdate.getMilliseconds() * 1000, 6);
      },
  
      // Timezone
      e: function() { // Timezone identifier; e.g. Atlantic/Azores, ...
        // The following works, but requires inclusion of the very large
        // timezone_abbreviations_list() function.
        /*              return that.date_default_timezone_get();
         */
        throw 'Not supported (see source code of date() for timezone on how to add support)';
      },
      I: function() { // DST observed?; 0 or 1
        // Compares Jan 1 minus Jan 1 UTC to Jul 1 minus Jul 1 UTC.
        // If they are not equal, then DST is observed.
        var a = new Date(f.Y(), 0);
        // Jan 1
        var c = Date.UTC(f.Y(), 0);
        // Jan 1 UTC
        var b = new Date(f.Y(), 6);
        // Jul 1
        var d = Date.UTC(f.Y(), 6); // Jul 1 UTC
        return ((a - c) !== (b - d)) ? 1 : 0;
      },
      O: function() { // Difference to GMT in hour format; e.g. +0200
        var tzo = jsdate.getTimezoneOffset();
        var a = Math.abs(tzo);
        return (tzo > 0 ? '-' : '+') + _pad(Math.floor(a / 60) * 100 + a % 60, 4);
      },
      P: function() { // Difference to GMT w/colon; e.g. +02:00
        var O = f.O();
        return (O.substr(0, 3) + ':' + O.substr(3, 2));
      },
      T: function() { // Timezone abbreviation; e.g. EST, MDT, ...
        // The following works, but requires inclusion of the very
        // large timezone_abbreviations_list() function.
        /*              var abbr, i, os, _default;
        if (!tal.length) {
          tal = that.timezone_abbreviations_list();
        }
        if (that.php_js && that.php_js.default_timezone) {
          _default = that.php_js.default_timezone;
          for (abbr in tal) {
            for (i = 0; i < tal[abbr].length; i++) {
              if (tal[abbr][i].timezone_id === _default) {
                return abbr.toUpperCase();
              }
            }
          }
        }
        for (abbr in tal) {
          for (i = 0; i < tal[abbr].length; i++) {
            os = -jsdate.getTimezoneOffset() * 60;
            if (tal[abbr][i].offset === os) {
              return abbr.toUpperCase();
            }
          }
        }
        */
        return 'UTC';
      },
      Z: function() { // Timezone offset in seconds (-43200...50400)
        return -jsdate.getTimezoneOffset() * 60;
      },
  
      // Full Date/Time
      c: function() { // ISO-8601 date.
        return 'Y-m-d\\TH:i:sP'.replace(formatChr, formatChrCb);
      },
      r: function() { // RFC 2822
        return 'D, d M Y H:i:s O'.replace(formatChr, formatChrCb);
      },
      U: function() { // Seconds since UNIX epoch
        return jsdate / 1000 | 0;
      }
    };
    this.date = function(format, timestamp) {
      that = this;
      jsdate = (timestamp === undefined ? new Date() : // Not provided
        (timestamp instanceof Date) ? new Date(timestamp) : // JS Date()
        new Date(timestamp * 1000) // UNIX timestamp (auto-convert to int)
      );
      return format.replace(formatChr, formatChrCb);
    };
    return this.date(format, timestamp);
  }
  
  function mktime() 
{
    
    var no=0, i = 0, ma=0, mb=0, d = new Date(), dn = new Date(), argv = arguments, argc = argv.length;

    var dateManip = {
        0: function (tt){ return d.setHours(tt); },
        1: function (tt){ return d.setMinutes(tt); },
        2: function (tt){ var set = d.setSeconds(tt); mb = d.getDate() - dn.getDate(); d.setDate(1); return set;},
        3: function (tt){ var set = d.setMonth(parseInt(tt, 10)-1); ma = d.getFullYear() - dn.getFullYear(); return set;},
        4: function (tt){ return d.setDate(tt+mb);},
        5: function (tt){
            if (tt >= 0 && tt <= 69) {
                tt += 2000;
            }
            else if (tt >= 70 && tt <= 100) {
                tt += 1900;
            }
            return d.setFullYear(tt+ma);
        }
        // 7th argument (for DST) is deprecated
    };

    for (i = 0; i < argc; i++){
        no = parseInt(argv[i]*1, 10);
        if (isNaN(no)) {
            return false;
        } else {
            // arg is number, let's manipulate date object
            if (!dateManip[i](no)){
                // failed
                return false;
            }
        }
    }
    for (i = argc; i < 6; i++) {
        switch (i) {
            case 0:
                no = dn.getHours();
                break;
            case 1:
                no = dn.getMinutes();
                break;
            case 2:
                no = dn.getSeconds();
                break;
            case 3:
                no = dn.getMonth()+1;
                break;
            case 4:
                no = dn.getDate();
                break;
            case 5:
                no = dn.getFullYear();
                break;
        }
        dateManip[i](no);
    }

    return Math.floor(d.getTime()/1000);
	
}

function CtrlSistema()
{
	
	// ##############################
	// ##############################
    
    var Req_CarregarDados;
    
	var ArCondicionado_OnOff;
	var ArCondicionado_Modo;
	var ArCondicionado_FanVelocidade;
	var ArCondicionado_PosicaoTipo;
	var ArCondicionado_Posicao;
    var ArCondicionado_Temperatura;
    var ArCondicionado_AutoDesligarID;
    var ArCondicionado_AutoDesligarTempo;
    var ArCondicionado_AutoDesligarDataFim;
	
	// ##############################
    
    this.ArCondicionado_OnOff		                = "On";
	this.ArCondicionado_Modo		                = "";
	this.ArCondicionado_FanVelocidade		        = "";
	this.ArCondicionado_PosicaoTipo		            = "";
	this.ArCondicionado_Posicao		                = "";
    this.ArCondicionado_Temperatura			        = 16;
    this.ArCondicionado_AutoDesligarID			    = -1;
    this.ArCondicionado_AutoDesligarTempo			= 0;
    this.ArCondicionado_AutoDesligarDataFim	        = 0;
	
	// ##############################
	// ##############################
	
	this.Init = function(){
		
		// -------------------
		
		var self = this;
		
		// -------------------
		
        self.InitEventos();
        
        // *******************

        self.ArCondicionado_InitEventos();
        self.ArCondicionado_InitAutoDesligar();
        
        // *******************

		self.Esp_CarregarDados();
		
		// -------------------
		
	};
	
	// ##############################
	// ##############################
	
	this.InitEventos = function(){
		
		// -------------------
		
		var self = this;
		
        // -------------------
        
        $(".BtnComandos").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
		
            var AssDados 						= {};
            AssDados["Modulo"] 					= "Comandos";
            AssDados["Comando"] 			    = $(this).attr("data-valor");
            AssDados["Comando2"] 			    = $(this).attr("data-valor2");
                
            // ********
    
            AssDadosJson                        = JSON.stringify(AssDados);
    
            // -------------------
            
            self.Esp_Enviar(AssDadosJson, AssDados["Comando"]);
    
            // -------------------
		
        });

        // -------------------
		
    };

    // ##############################
	// ##############################
	
	this.ArCondicionado_InitEventos = function(){
		
		// -------------------
		
		var self = this;
        
        // -------------------
		
		$("#EstArCondicionado .BtnDesligar").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
			
            self.ArCondicionado_OnOff           = "Off";

            // ********

            self.ArCondicionado_Enviar();

			// -------------------
		
        });

        // -------------------
		
		$("#EstArCondicionado .BtnLigar").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
			
            self.ArCondicionado_OnOff           = "On";

            // ********

            self.ArCondicionado_Enviar();

			// -------------------
		
        });

        // -------------------
		
		$("#EstArCondicionado .BtnModo").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
            
            DadValor                            = $(this).attr("data-valor");
            
            $("#EstArCondicionado .BtnModo").removeClass("active");
            $("#EstArCondicionado .BtnModo_" + DadValor).addClass("active");

            // ********

            self.ArCondicionado_OnOff           = "On";
            self.ArCondicionado_Modo            = DadValor;

            // ********

            self.ArCondicionado_Enviar();
			
			// -------------------
		
        });

        // -------------------
		
		$("#EstArCondicionado .BtnFanVelocidade").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
            
            DadValor                            = $(this).attr("data-valor");
            
            $("#EstArCondicionado .BtnFanVelocidade").removeClass("active");
            $("#EstArCondicionado .BtnFanVelocidade_" + DadValor).addClass("active");

            // ********

            self.ArCondicionado_OnOff           = "On";
            self.ArCondicionado_FanVelocidade   = DadValor;

            // ********

            self.ArCondicionado_Enviar();
			
			// -------------------
		
        });

        // -------------------
		
		$("#EstArCondicionado .BtnFanPosicaoTipo").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
            
            DadValor                            = $(this).attr("data-valor");
            
            $("#EstArCondicionado .BtnFanPosicaoTipo").removeClass("active");
            $("#EstArCondicionado .BtnFanPosicaoTipo_" + DadValor).addClass("active");

            // ********

            self.ArCondicionado_OnOff           = "On";
            self.ArCondicionado_PosicaoTipo     = DadValor;

            // ********

            self.ArCondicionado_Enviar();
			
			// -------------------
		
        });

        // -------------------
		
		$("#EstArCondicionado .BtnFanPosicao").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
            
            DadValor                            = $(this).attr("data-valor");
            
            $("#EstArCondicionado .BtnFanPosicao").removeClass("active");
            $("#EstArCondicionado .BtnFanPosicao_" + DadValor).addClass("active");

            // ********

            self.ArCondicionado_OnOff           = "On";
            self.ArCondicionado_Posicao         = Posicao;

            // ********

            self.ArCondicionado_Enviar();
			
			// -------------------
		
        });

        // -------------------
		
		$("#EstArCondicionado #BtnTemperatura .dropdown-menu a").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
            
            DadValor                            = $(this).attr("data-valor");
            
            // ********

            self.ArCondicionado_Temperatura     = DadValor;
            self.ArCondicionado_OnOff           = "On";

            // ********

            self.ArCondicionado_Carregar_Temperatura();
            self.ArCondicionado_Enviar();

            // -------------------
		
        });
        
        // -------------------
		
		$("#EstArCondicionado #BtnTemperaturaCtrlMais").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
			
            if( self.ArCondicionado_Temperatura < 30 )
            {

                // -------------------

                self.ArCondicionado_Temperatura++;
                self.ArCondicionado_OnOff           = "On";

                // ********

                self.ArCondicionado_Carregar_Temperatura();
                self.ArCondicionado_Enviar();

                // -------------------

            }
			
			// -------------------
		
        });
        
        // -------------------
		
		$("#EstArCondicionado #BtnTemperaturaCtrlMenos").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
			
            if( self.ArCondicionado_Temperatura > 16 )
            {

                // -------------------

                self.ArCondicionado_Temperatura--;
                self.ArCondicionado_OnOff           = "On";

                // ********

                self.ArCondicionado_Carregar_Temperatura();
                self.ArCondicionado_Enviar();

                // -------------------

            }
			
			// -------------------
		
        });
        
        // -------------------
		
		$("#EstArCondicionado .BtnPreDefinicao").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
            
            DadValor                                = $(this).attr("data-valor");
            DadValorSep                             = DadValor.split("_");

            // ********

            self.ArCondicionado_OnOff               = "On";
            self.ArCondicionado_Modo		        = DadValorSep[0];
            self.ArCondicionado_FanVelocidade		= DadValorSep[1];
            self.ArCondicionado_PosicaoTipo		    = DadValorSep[2];
            self.ArCondicionado_Posicao		        = DadValorSep[3];
            self.ArCondicionado_Temperatura		    = DadValorSep[4];

            // ********

            self.ArCondicionado_Carregar();
            self.ArCondicionado_Enviar();
			
			// -------------------
		
        });

        // -------------------
		
		$("#EstArCondicionado .BtnAutoDesligar").click(function(e){
		
			// -------------------
			
			e.preventDefault();
			
			// -------------------
            
            DadValor                                = parseInt($(this).attr("data-valor"));
            
            // ********

            var AssDados 						    = {};
            AssDados["Modulo"] 					    = "ArCondicionado_AutoDesligar";
            AssDados["Tempo"] 					    = DadValor;
            AssDados["DataFinal"] 					= mktime() + DadValor;
            
            // ********
    
            AssDadosJson                            = JSON.stringify(AssDados);
    
            // -------------------
            
            self.Esp_Enviar(AssDadosJson);    

			// -------------------
		
        });
		
		// -------------------
		
    };

    // ##############################
	
	this.ArCondicionado_Carregar_Temperatura = function(){
		
		// -------------------
		
		var self = this;
		
        // -------------------
		
        $("#BlcTemperatura").html(self.ArCondicionado_Temperatura);

		// -------------------
		
    };

    // ##############################
	
	this.ArCondicionado_Carregar = function(){
		
		// -------------------
		
		var self = this;
		
        // -------------------
        
        $("#EstArCondicionado .BtnModo").removeClass("active");
        $("#EstArCondicionado .BtnModo_" + self.ArCondicionado_Modo).addClass("active");

        // ********

        $("#EstArCondicionado .BtnFanVelocidade").removeClass("active");
        $("#EstArCondicionado .BtnFanVelocidade_" + self.ArCondicionado_FanVelocidade).addClass("active");

        // ********

        $("#EstArCondicionado .BtnFanPosicaoTipo").removeClass("active");
        $("#EstArCondicionado .BtnFanPosicaoTipo_" + self.ArCondicionado_PosicaoTipo).addClass("active");

        // ********

        $("#EstArCondicionado .BtnFanPosicao").removeClass("active");
        $("#EstArCondicionado .BtnFanPosicao_" + self.ArCondicionado_Posicao).addClass("active");

        // ********

        $("#BlcTemperatura").html(self.ArCondicionado_Temperatura);

        // ********

        if( self.ArCondicionado_AutoDesligarID >= 0 )
        {

            $("#EstArCondicionado #BlcAutoDesligar_N").hide();
            $("#EstArCondicionado #BlcAutoDesligar_S").show();

        }else{

            $("#EstArCondicionado #BlcAutoDesligar_N").show();
            $("#EstArCondicionado #BlcAutoDesligar_S").hide();

        }

		// -------------------
		
    };
    
    // ##############################
	
	this.ArCondicionado_Enviar = function(){
		
		// -------------------
		
		var self = this;
		
        // -------------------
		
        var AssDados 						= {};
        AssDados["Modulo"] 					= "ArCondicionado";
        AssDados["OnOff"] 					= self.ArCondicionado_OnOff;
        AssDados["Modo"] 					= $("#EstArCondicionado .BtnModo.active").attr("data-valor");
        AssDados["FanVelocidade"] 		    = $("#EstArCondicionado .BtnFanVelocidade.active").attr("data-valor");
        AssDados["PosicaoTipo"] 		    = $("#EstArCondicionado .BtnFanPosicaoTipo.active").attr("data-valor");
        AssDados["Posicao"] 			    = $("#EstArCondicionado .BtnFanPosicao.active").attr("data-valor");
        AssDados["Temperatura"] 		    = self.ArCondicionado_Temperatura;
            
        // ********

        AssDadosJson                        = JSON.stringify(AssDados);

        // -------------------
        
        self.Esp_Enviar(AssDadosJson);

		// -------------------
		
    };
    
    // ##############################
	
	this.ArCondicionado_InitAutoDesligar = function(){
		
		// -------------------
		
		var self = this;
		
        // -------------------
		
		setInterval(function(){
			
            // -------------------
            
            if( self.ArCondicionado_AutoDesligarID >= 0 )
            {

                // -------------------

                DadTempo    = self.ArCondicionado_AutoDesligarDataFim - mktime();
                
                // *******************

                if( DadTempo > 0 )
                {
                    
                    // -------------------

                    Tempo		= DadTempo;

                    day 		= Math.floor(Tempo / 86400);
                    hours 		= Math.floor((Tempo - ( day * 86400 )) / 3600);
                    minutes 	= Math.floor((Tempo - ( day * 86400 ) - ( hours * 3600 )) / 60);
                    seconds 	= Math.round(Tempo - ( day * 86400 ) - ( hours * 3600 ) - ( minutes * 60 ));
                    
                    day 		= ("00" + day).substring(("00" + day).length-2);
                    hours 		= ("00" + hours).substring(("00" + hours).length-2);
                    minutes 	= ("00" + minutes).substring(("00" + minutes).length-2);
                    seconds 	= ("00" + seconds).substring(("00" + seconds).length-2);

                    minutes 	= ("00" + minutes).substring(("00" + minutes).length-2);
                    seconds 	= ("00" + seconds).substring(("00" + seconds).length-2);

                    ExtText1	= "";

                    if( parseInt(day) > 0 ){

                        ExtText1		= day + "d : " + hours + "h : " + minutes + "m : " + seconds + "s";
                        
                    }else if( parseInt(hours) > 0 ){

                        ExtText1		= hours + "h : " + minutes + "m : " + seconds + "s";
                        
                    }else if( parseInt(minutes) > 0 ){

                        ExtText1		= minutes + "m : " + seconds + "s";

                    }else{

                        ExtText1		= seconds + "s";

                    }
                    
                    // -------------------
                    
                }else{
                    
                    // -------------------
                    
                    if( DadTempo == -5 )
                    {
                       
                        self.Esp_CarregarDados();

                    }

                    // -------------------

                    ExtText1		= "Desligando...";
                    
                    // -------------------
                    
                }
                
                // -------------------

                $("#BlcAutoDesligar_TempoRestante").html(ExtText1);

                // -------------------

            }
            
            // -------------------
			
        }, 1000);
        
        // -------------------
		
    };
    
    // ##############################
    // ##############################
	
	this.Esp_CarregarDados = function(){
		
		// -------------------
		
		var self = this;
		
        // -------------------
        
        clearTimeout(self.Req_CarregarDados);

        // ********

        req = $.ajax({								
            type: 		    "GET",
            url: 		    "/dados_json/",
            dataType:       "json",
            contentType:    "application/json",
            success: 	    function(msg)
            {
                
                // -------------------
                
                self.ArCondicionado_OnOff                   = msg.ArCondicionado_OnOff;
                self.ArCondicionado_Modo		            = msg.ArCondicionado_Modo;
                self.ArCondicionado_FanVelocidade		    = msg.ArCondicionado_FanVelocidade;
                self.ArCondicionado_PosicaoTipo		        = msg.ArCondicionado_PosicaoTipo;
                self.ArCondicionado_Posicao		            = msg.ArCondicionado_Posicao;
                self.ArCondicionado_Temperatura		        = parseInt(msg.ArCondicionado_Temperatura);

                self.ArCondicionado_AutoDesligarID		    = parseInt(msg.ArCondicionado_AutoDesligarID);
                self.ArCondicionado_AutoDesligarTempo	    = parseInt(msg.ArCondicionado_AutoDesligarTempo);
                self.ArCondicionado_AutoDesligarDataFim     = parseInt(msg.ArCondicionado_AutoDesligarDataFim);

                // ********

                self.ArCondicionado_Carregar();

                // -------------------

                self.Req_CarregarDados                      = window.setTimeout("ObjCtrlSistema.Esp_CarregarDados()", 30000);

                // -------------------
                
            },error: function(objRequest){

                // -------------------
                
                self.Req_CarregarDados                      = window.setTimeout("ObjCtrlSistema.Esp_CarregarDados()", 30000);

                // -------------------
            
            }
        });	

		// -------------------
		
    };
    
    // ##############################
	
	this.Esp_Enviar = function(DadosJson, Comando){
		
		// -------------------
		
        var self = this;
        
        // -------------------

        Comando = Comando || "";
		
        // -------------------
		
        $.ajax({								
            type: 		    "POST",
            url: 		    "/comandos_json/",
            data: 		    DadosJson,
            dataType:       "json",
            contentType:    "application/json",
            success: 	    function(msg)
            {
                
                // -------------------

                self.Esp_CarregarDados();

                // -------------------

                switch(Comando)
                {

                    case "DebugRemotoOn":

                        ObjCtrlDebugRemoto.AccIniciar();
                        
                    break;

                    case "DebugRemotoOff":
                        
                        ObjCtrlDebugRemoto.AccParar();

                    break;

                }

                // -------------------

            }
        });	

		// -------------------
		
	};
	
	// ##############################
    // ##############################
    
}

function CtrlDebugRemoto()
{
	
	// ##############################
	// ##############################
    
    var Sck_Ws;
    var Sck_Host;

    // ##############################
    
    this.Sck_Host           = "ws://192.168.20.100:81/";
	
	// ##############################
	// ##############################
	
	this.AccIniciar = function(){
		
		// -------------------
		
		var self2 = this;
		
		// -------------------
		
        self2.Sck_Ws 		    = new WebSocket(self2.Sck_Host);
		
		self2.Sck_Ws.onopen = function(e) {
            
            console.log(e);
            
			self2.AccMensagem("WebSocket - onopen");
			
		};
		self2.Sck_Ws.onmessage = function(e) {
            
			self2.AccMensagem(e.data);
			
		};
		self2.Sck_Ws.onclose = function(e) {
            
            console.log(e);

			self2.AccMensagem("WebSocket - onclose");
			
		};
		self2.Sck_Ws.onerror = function(e) {
            
            console.log(e);
            
            self2.AccMensagem("WebSocket - onerror");
            
		};
        
		// -------------------
		
	};
	
    // ##############################

    this.AccParar = function(){
		
		// -------------------
		
		var self2 = this;
		
		// -------------------
		
        self2.Sck_Ws.close();
        
		// -------------------
		
	};
	
	// ##############################
    // ##############################

    this.AccMensagem = function(Mensagem){
		
		// -------------------
		
		var self2 = this;
		
		// -------------------
		
        $("#BlcMensagens").append('<p><span class="label label-default">' + date('d/m/Y H:i:s') + '</span> ' + Mensagem + '</p>');

        // -------------------

        if( $("#DebugRemoto_IsScrool").is(":checked") )
        {
            
            $('#BlcMensagensRedor').scrollTop($('#BlcMensagensRedor').get(0).scrollHeight);

        }

		// -------------------
		
	};
	
	// ##############################
    // ##############################
    
}