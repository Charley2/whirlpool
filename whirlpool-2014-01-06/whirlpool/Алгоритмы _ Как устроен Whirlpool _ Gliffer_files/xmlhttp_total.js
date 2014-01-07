
var my_base_url='http://gliffer.ru';
var my_pligg_base='';


dochref = document.location.href.substr(document.location.href.search('/')+2, 1000);
if(dochref.search('/') == -1){
	$thisurl = document.location.href.substr(0,document.location.href.search('/')+2) + dochref;
} else {
	$thisurl = document.location.href.substr(0,document.location.href.search('/')+2) + dochref.substr(0, dochref.search('/'));
}
$thisurl = $thisurl + '';

var xmlhttp
/*@cc_on @*/
/*@if (@_jscript_version >= 5)
  try {
  xmlhttp=new ActiveXObject("Msxml2.XMLHTTP")
 } catch (e) {
  try {
	xmlhttp=new ActiveXObject("Microsoft.XMLHTTP")
  } catch (E) {
   xmlhttp=false
  }
 }
@else
 xmlhttp=false
@end @*/

if (!xmlhttp && typeof XMLHttpRequest != 'undefined')
{
  try {
	xmlhttp = new XMLHttpRequest ();
  }
  catch (e) {
  xmlhttp = false}
}

function myXMLHttpRequest ()
{
  var xmlhttplocal;
  try {
  	xmlhttplocal = new ActiveXObject ("Msxml2.XMLHTTP")}
  catch (e) {
	try {
	xmlhttplocal = new ActiveXObject ("Microsoft.XMLHTTP")}
	catch (E) {
	  xmlhttplocal = false;
	}
  }

  if (!xmlhttplocal && typeof XMLHttpRequest != 'undefined') {
	try {
	  var xmlhttplocal = new XMLHttpRequest ();
	}
	catch (e) {
	  var xmlhttplocal = false;
	}
  }
  return (xmlhttplocal);
}

var mnmxmlhttp = Array ();
var xvotesString = Array ();
var mnmPrevColor = Array ();
var responsestring = Array ();
var myxmlhttp = Array ();
var responseString = new String;


function vote (user, id, htmlid, md5, value)
{
  	if (xmlhttp) {
		url = $thisurl + "/vote_total.php";
		var mycontent = "id=" + id + "&user=" + user + "&md5=" + md5 + "&value=" + value;
		anonymous_vote = true ;
        if (anonymous_vote == false && user == '0') {
            window.location="http://gliffer.ru/login.php?return="+location.href;
        } else {
    		mnmxmlhttp[htmlid] = new myXMLHttpRequest ();
    		if (mnmxmlhttp) {
    			mnmxmlhttp[htmlid].open ("POST", url, true);
    			mnmxmlhttp[htmlid].setRequestHeader ('Content-Type',
    					   'application/x-www-form-urlencoded');
    
    			mnmxmlhttp[htmlid].send (mycontent);
    			errormatch = new RegExp ("^ERROR:");    
    			target1 = document.getElementById ('xvotes-' + htmlid);    
    			mnmPrevColor[htmlid] = target1.style.backgroundColor;
    			mnmxmlhttp[htmlid].onreadystatechange = function () {
    				if (mnmxmlhttp[htmlid].readyState == 4) {
    					xvotesString[htmlid] = mnmxmlhttp[htmlid].responseText;
    					if (xvotesString[htmlid].match (errormatch)) {
    						xvotesString[htmlid] = xvotesString[htmlid].substring (6, xvotesString[htmlid].length);
							changemnmvalues (htmlid, value, true);    					} else {
														if (xvotesString[htmlid].substring (1, 6) == "ERROR") { alert(xvotesString[htmlid]);  } else {changemnmvalues (htmlid, value, false); }     					}
    				}
    			}
    		}
    	}
	}
}


function unvote (user, id, htmlid, md5, value)
{
  	if (xmlhttp) {
		url = $thisurl + "/vote_total.php";
		var mycontent = "unvote=true&id=" + id + "&user=" + user + "&md5=" + md5 + "&value=" + value;
		anonymous_vote = true ;
        if (anonymous_vote == false && user == '0') {
            window.location="http://gliffer.ru/login.php?return="+location.href;
        } else {
    		mnmxmlhttp[htmlid] = new myXMLHttpRequest ();
    		if (mnmxmlhttp) {
    			mnmxmlhttp[htmlid].open ("POST", url, true);
    			mnmxmlhttp[htmlid].setRequestHeader ('Content-Type',
    					   'application/x-www-form-urlencoded');
    
    			mnmxmlhttp[htmlid].send (mycontent);
    			errormatch = new RegExp ("^ERROR:");    
				target1 = document.getElementById ('xvotes-' + htmlid);
  				target2 = document.getElementById ('xvote-' + htmlid);    
    			mnmPrevColor[htmlid] = target1.style.backgroundColor;
    			mnmxmlhttp[htmlid].onreadystatechange = function () {
    				if (mnmxmlhttp[htmlid].readyState == 4) {
    					xvotesString[htmlid] = mnmxmlhttp[htmlid].responseText;
    					if (xvotesString[htmlid].match (errormatch)) {
    						 xvotesString[htmlid] = xvotesString[htmlid].substring (6, xvotesString[htmlid].length);
							changemnmvalues (htmlid, value, true);target2.innerHTML = "<span>Голосовать</span>";						} else {
							if (xvotesString[htmlid].substring (1, 6) == "ERROR") { alert(xvotesString[htmlid]);  } else {target2.innerHTML = "<span>Голосовать</span>";changemnmvalues (htmlid, value, false); }							
    					}
    				}
    			}
    		}
    	}
	}
}


function cvote (user, id, htmlid, md5, value)
{
	if (xmlhttp) {
		url = $thisurl + "/cvote.php";
		mycontent = "id=" + id + "&user=" + user + "&md5=" + md5 + "&value=" + value;
		anonymous_vote = true ;

        if (anonymous_vote == false && user == '0') {
            window.location="http://gliffer.ru/login.php?return="+location.href;
        } else {
    		mnmxmlhttp[htmlid] = new myXMLHttpRequest ();
    		if (mnmxmlhttp) {
    			mnmxmlhttp[htmlid].open ("POST", url, true);
    			mnmxmlhttp[htmlid].setRequestHeader ('Content-Type', 'application/x-www-form-urlencoded');    
    			mnmxmlhttp[htmlid].send (mycontent);
    			errormatch = new RegExp ("^ERROR:");
    			target1 = document.getElementById ('cvote-' + htmlid);        
    			mnmPrevColor[htmlid] = target1.style.backgroundColor;
    			target1.style.backgroundColor = '#FFFFFF';
    			mnmxmlhttp[htmlid].onreadystatechange = function () {
    				if (mnmxmlhttp[htmlid].readyState == 4) {
    					xvotesString[htmlid] = mnmxmlhttp[htmlid].responseText;
    					if (xvotesString[htmlid].match (errormatch)) {
    						xvotesString[htmlid] = xvotesString[htmlid].substring (6, xvotesString[htmlid].length);						
    						changecvotevalues (htmlid, true);							
    					} else {
							target1 = document.getElementById ('ratebuttons-' + id);
							target1.style.display = "none";
							target2 = document.getElementById ('ratetext-' + id);
							target2.innerHTML = "Спасибо за оценку этого комментария.";
							changecvotevalues (htmlid, false);
    					}
    				}
    			}
    		}
    	}
	}
}

function changemnmvalues (id, value, error)
{
	split = new RegExp ("~--~");
	b = xvotesString[id].split (split);
	target1 = document.getElementById ('xvotes-' + id);
	target2 = document.getElementById ('xvote-' + id);
	target3 = document.getElementById ('xreport-' + id);
	target4 = document.getElementById ('xnews-' + id);
//	if (error) {
//		if (value > 0) { target2.innerHTML = "<span>голосов</span> "; }
//		else if (value < 0) { target2.innerHTML = "<span>Против</span> "; }
//		return false;
//	}
	if (b.length <= 3) {
		if (error) {
			alert(b[0]);
			return false;
		}
		target1.innerHTML = b[0];
		target1.style.backgroundColor = mnmPrevColor[id];
//		new Effect.Fade(target3);
		if (value > 0) { target2.innerHTML = "<span>голосов</span> "; }
		else if (value < 0 ) { target2.innerHTML = "<span>Против</span> ";
//		new Effect.Opacity(target4, {duration:0.8, from:1.0, to:0.3}); 
		}
	}
	return false;
}

function changecvotevalues (id, error)
{
	split = new RegExp ("~--~");
	b = xvotesString[id].split (split);
	target1 = document.getElementById ('cvote-' + id);
	if (error) {
		return false;
	}
	if (b.length <= 3) {
		target1.innerHTML = b[0];
		target1.style.backgroundColor = mnmPrevColor[id];
	}
	return false;
}


function enablebutton (button, button2, target)
{
	var string = target.value;
	button2.disabled = false;
	if (string.length > 0) {
		button.disabled = false;
	} else {
		button.disabled = true;
	}
}

function checkfield (type, form, field)
{
	url = $thisurl + '/checkfield.php?type='+type;
	checkitxmlhttp = new myXMLHttpRequest ();
	checkitxmlhttp.open ("POST", url, true);
	checkitxmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	checkitxmlhttp.onreadystatechange = function () {
		if (checkitxmlhttp.readyState == 4) {
		responsestring = checkitxmlhttp.responseText;
			if (responsestring == 'OK') {
				document.getElementById (field.name+'checkitvalue').innerHTML = '<span style="color:black">"' + field.value + 
						'": ' + responsestring + '</span>';
				form.submit.disabled = '';
			} else {
				document.getElementById (field.name+'checkitvalue').innerHTML = '<span style="color:red">"' +
				responsestring + '</span>';
				form.submit.disabled = '';
			}
		}
	}
  checkitxmlhttp.send ('name=' + field.value);
  return false;
}

function emailto (original_id, htmlid, instpath, address_count)
{
	email_message = document.getElementById('email_message' + htmlid).value;
	email_address = document.getElementById('email_address_1_' + htmlid).value;
	if (address_count > 1){ 
		for ($i = 2; $i <= address_count; $i++) {
			if(document.getElementById('email_address_' + $i + '_' + htmlid).value != "") {
				email_address = email_address + ', ' + document.getElementById('email_address_' + $i + '_' + htmlid).value;
			}
		}
	}
	
	if (xmlhttp) {
		url = $thisurl + "/recommend.php";
		mycontent = "token=" + document.getElementById('email_message' + htmlid).form.token.value + "&email_address=" + escape(email_address) + "&email_to_submit=submit&email_message=" + escape(email_message) + "&original_id=" + original_id + "&backup=0";
		target2 = document.getElementById ('emailto-' + htmlid);
		target2.innerHTML = "<br>Sending, please wait....";
		
		mnmxmlhttp[htmlid] = new myXMLHttpRequest ();
		if (mnmxmlhttp) {
			mnmxmlhttp[htmlid].open ("POST", url, true);
			mnmxmlhttp[htmlid].setRequestHeader ('Content-Type',
					   'application/x-www-form-urlencoded');

			mnmxmlhttp[htmlid].send (mycontent);
			errormatch = new RegExp ("^ERROR:");
			target1 = document.getElementById ('emailto-' + htmlid);
			mnmxmlhttp[htmlid].onreadystatechange = function () {
				if (mnmxmlhttp[htmlid].readyState == 4) {
					xvotesString[htmlid] = mnmxmlhttp[htmlid].responseText;
			
					if (xvotesString[htmlid].match (errormatch)) {
						xvotesString[htmlid] = xvotesString[htmlid].substring (6, xvotesString[htmlid].length);						
						target2 = document.getElementById ('emailto-' + htmlid);
						target2.innerHTML = xvotesString[htmlid];						
					} else {
						target2 = document.getElementById ('emailto-' + htmlid);
						target2.innerHTML = xvotesString[htmlid];
					}
				}
			}
		}
	}
}

function show_recommend(htmlid, linkid, instpath)
{
	var emailtodisplay=document.getElementById('emailto-' + htmlid).style.display ? '' : 'none';
	document.getElementById('emailto-' + htmlid).style.display = emailtodisplay;

	if (xmlhttp) {
		url = $thisurl + "/recommend.php";
		mycontent = "draw=small&htmlid=" + htmlid + "&linkid=" + linkid;
		target2 = document.getElementById ('emailto-' + htmlid);
		target2.innerHTML = "<br>Loading, please wait....";		
		mnmxmlhttp[htmlid] = new myXMLHttpRequest ();
		
		if (mnmxmlhttp) {
			mnmxmlhttp[htmlid].open ("POST", url, true);
			mnmxmlhttp[htmlid].setRequestHeader ('Content-Type',
					   'application/x-www-form-urlencoded');

			mnmxmlhttp[htmlid].send (mycontent);
			errormatch = new RegExp ("^ERROR:");
			target1 = document.getElementById ('emailto-' + htmlid);
			mnmxmlhttp[htmlid].onreadystatechange = function () {
				if (mnmxmlhttp[htmlid].readyState == 4) {
					xvotesString[htmlid] = mnmxmlhttp[htmlid].responseText;			
					if (xvotesString[htmlid].match (errormatch)) {
						xvotesString[htmlid] = xvotesString[htmlid].substring (6, xvotesString[htmlid].length);						
						target2 = document.getElementById ('emailto-' + htmlid);
						target2.innerHTML = xvotesString[htmlid];						
					} else {
						target2 = document.getElementById ('emailto-' + htmlid);
						target2.innerHTML = xvotesString[htmlid];
					}
				}
			}
		}
	}
}

function show_hide_user_links(thediv)
{
//	if(window.Effect){
//		if(thediv.style.display == 'none')
//		{Effect.Appear(thediv); return false;}
//		else
//		{Effect.Fade(thediv); return false;}
//	}else{
		var replydisplay=thediv.style.display ? '' : 'none';
		thediv.style.display = replydisplay;					
//	}
}

