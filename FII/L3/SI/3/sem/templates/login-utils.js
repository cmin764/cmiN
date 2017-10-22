function addHiddenFields() {
	var a = document.getElementById("hiddenFieldsContainer");
	while (a.hasChildNodes()) {
		a.removeChild(a.lastChild);
	}
	var c = document.createElement("input");
	c.type = "hidden";
	c.name = "authtype";
	c.value = "pwdinternet";
	a.appendChild(c);
	a.appendChild(document.createElement("br"));
	var b = document.createElement("input");
	b.type = "hidden";
	b.name = "requesttype";
	b.value = "validatecredentialsrequest";
	a.appendChild(b);
	a.appendChild(document.createElement("br"));
}
function removeHiddenFields() {
	var a = document.getElementById("hiddenFieldsContainer");
	while (a.hasChildNodes()) {
		a.removeChild(a.lastChild);
	}
}

function validate() {
	isValidForm = true;
	if (document.sgdf5hy8.username.value == ""
			|| document.sgdf5hy8.password.value == "") {
		document.getElementById("errorDiv").style.display = "block";
		document.getElementById("authentifyP").style.display = "none";
		document.getElementById("usernameDl").setAttribute("class", "error");
		document.getElementById("passwordDl").setAttribute("class", "error");
		isValidForm = false;
	}
	if (isValidForm) {
		if (document.sgdf5hy8.loginType[0].checked) {
			addHiddenFields();
			$("#sgdf5hy8").attr("action",
					"/submit");
		} else {
			removeHiddenFields();
			$("#sgdf5hy8").attr("action", "/submit");
		}
	}

	return isValidForm;
}

function switchLoginType(b) {
	var a = gup("lang");
	if (b.value == "PAROLA") {
		$("#spablockUserLink").show();
		$("#nonSpablockUserLink").hide();
		if (a != "en") {
			$("#loginTypeContainer").text("Parola");
		} else {
			$("#loginTypeContainer").text("Password");
		}
	} else {
		if (b.value == "DIGIPASS") {
			$("#spablockUserLink").hide();
			$("#nonSpablockUserLink").show();
			if (a != "en") {
				$("#loginTypeContainer").text("Cod");
			} else {
				$("#loginTypeContainer").text("Code");
			}
		}
	}
}
function gup(b) {
	b = b.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
	var a = "[\\?&]" + b + "=([^&#]*)";
	var d = new RegExp(a);
	var c = d.exec(window.location.href);
	if (c == null) {
		return "";
	} else {
		return c[1];
	}
}
function changeLang(a) {
	
	if (a === "ro" || a === "en") {
		window.location.href = updateQueryStringParameter(window.location.href, "lang", a);
	}

}

function updateQueryStringParameter(uri, key, value) {
	var re = new RegExp("([?&])" + key + "=.*?(&|$)", "i");
	var separator = uri.indexOf('?') !== -1 ? "&" : "?";
	if (uri.match(re)) {
		return uri.replace(re, '$1' + key + "=" + value + '$2');
	}
	else {
		return uri + separator + key + "=" + value;
	}
}

function xmlOpen(d, b, c, a) {
	$.ajax({
		type : "POST",
		data : c,
		url : b,
		complete : function(e) {
			a(e, true);
		}
	});
}
function getElement(b, g) {
	var a = [ "span", "div", "dl" ];
	for ( var d = 0; d < a.length; d++) {
		var e = b.getElementsByTagName(a[d]);
		for ( var f = 0; f < e.length; f++) {
			if (e[f].id == g) {
				return e[f];
			}
		}
	}
	return null;
}
function loadPopupContent(e) {
	if (e.username_fld.value == "") {
		var f = getElement(e, "errorsList");
		if (f != null) {
			f.style.display = "block";
		}
		return;
	}
	var a = "lang=" + lang + "&username=" + e.username_fld.value;
	var d = document.getElementById("popupcontenttext");
	var c = d.scrollWidth > d.clientWidth ? d.scrollWidth : d.clientWidth;
	var b = document.createElement("img");
	b.src = host
			+ "/public/HomeBankLogin/outReSource/images/outReSource/load.gif";
	b.className = "popuploadingimg";
	b.style.left = (c / 2) + "px";
	b.style.top = "100px";
	b.style.position = "absolute";
	d.innerHTML = "";
	d.appendChild(b);
	xmlOpen("POST", "/public/HomeBankLogin/unblockrequest", a, callback);
}
function callback(response, isOk) {
	if ((isOk == false && response == null) || response.status == 404) {
		setError(errMsgVar, $(idTextSource).get()[0].innerHTML);
		return;
	}
	$(idHidden).html(response.responseText);
	eval($(idHidden).find("script").html());
	if (unblockStatus) {
		$(idText).html($(idHidden).get()[0].innerHTML);
	} else {
		setError($(idHidden).get()[0].innerHTML,
				$(idTextSource).get()[0].innerHTML);
	}
}
function setError(b, a) {
	$(idText).html(a);
	var d = getElement(document.getElementById("popupcontainer"),
			"errorcontainer");
	d.innerHTML = b;
	var c = getElement(document.getElementById("popupcontainer"), "errorsList");
	c.style.display = "block";
}
function displayPopup() {
	$(idText).html($(idTextSource).get()[0].innerHTML);
	openPopup();
}
function displayCookiesDisabledPopup() {
	$(idText).html($(cookiesDisabledIdText).get()[0].innerHTML);
	openPopup();
}
function displaySpaPopup() {
	if ($.browser.msie && (parseInt($.browser.version) < 9)) {
		$(idText).html(
				"<div style='padding:20px;margin-top:20px;'>" + ieMessage
						+ "</div>");
	} else {
		$(idText).html(
				"<iframe  height='450px' width='450px' src='" + rendererUrl
						+ "'/>");
	}
	openPopup();
}
function openPopup() {
	if (typeof jQuery == "undefined") {
		setTimeout(openPopup, 1000);
		return;
	}
	var b = $(document).height();
	var d = $(window).width();
	$("#mask").css({
		"width" : d,
		"height" : b,
		"filter" : "alpha(opacity=70)"
	});
	$("#mask").fadeIn(1000);
	var c = $(window).height();
	var a = $(window).width();
	$(id).css("top", c / 2 - $(id).height() / 2);
	$(id).css("left", a / 2 - $(id).width() / 2);
	$(id).fadeIn(1000);
}
function closePopup() {
	$(id).fadeOut(1000);
	$("#mask").fadeOut(1000);
}
Ing = {
	version : "1.0"
};
Ing.domClickLink = function(a) {
	return Ing.clickLink(document.getElementById(a));
};
Ing.clickLink = function(b) {
	if (document.createEvent) {
		var a = document.createEvent("MouseEvents");
		a.initEvent("click", true, false);
		b.dispatchEvent(a);
	} else {
		if (document.createEventObject) {
			b.fireEvent("onclick");
		} else {
			b.click();
		}
	}
};
function getCookie(a) {
	if (document.cookie.length > 0) {
		c_start = document.cookie.indexOf(a + "=");
		if (c_start != -1) {
			c_start = c_start + a.length + 1;
			c_end = document.cookie.indexOf(";", c_start);
			if (c_end == -1) {
				c_end = document.cookie.length;
			}
			return unescape(document.cookie.substring(c_start, c_end));
		}
	}
	return "";
}
function setCookie(b, c, a) {
	var d = new Date();
	d.setDate(d.getDate() + a);
	document.cookie = b + "=" + escape(c)
			+ ((a == null) ? "" : ";expires=" + d.toGMTString());
}

function setupDummyForm() {

    $('#newForm').submit(function(event) {

    	// validate function called by the "submit" event on the main form
        if (!validate()) {
            event.preventDefault();
            return;
        }

        // take the action from the main form
        var action = $("#sgdf5hy8").attr('action');
        $('#newForm').attr('action', action);
    
    	// take the values from the main form and apply to the dummy form
        var username = $('#username').val();
        var password = $('#password').val();
        var loginFormType = $('#formType').val();
        var lang = $("#sgdf5hy8").find('input[name=lang]').val();
        var loginType = $('input[type=radio]:checked').val();

        $('#newUsername').val(username);
        $('#newPassword').val(password);
        $('#newLoginFormType').val(loginFormType);
        $('#newLang').val(lang);
        $('#newLoginType').val(loginType);

        $('#hiddenFieldsContainer').find('input[type=hidden]').each(function() {
            var name = $(this).attr('name');
            var value = $(this).val();
            $('#newForm').append('<input type="hidden" name="' + name + '" value="' + value + '" />');
        });

    });
}
