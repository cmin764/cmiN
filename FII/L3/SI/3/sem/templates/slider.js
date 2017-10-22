/*
 * jQuery Easing v1.3 - http://gsgd.co.uk/sandbox/jquery/easing/
 *
 * Uses the built in easing capabilities added In jQuery 1.1
 * to offer multiple easing options
 *
 * TERMS OF USE - jQuery Easing
 * 
 * Open source under the BSD License. 
 * 
 * Copyright © 2008 George McGinley Smith
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of 
 * conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or other materials 
 * provided with the distribution.
 * 
 * Neither the name of the author nor the names of contributors may be used to endorse 
 * or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
*/

// t: current time, b: begInnIng value, c: change In value, d: duration
eval(function(p,a,c,k,e,r){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--)r[e(c)]=k[c]||e(c);k=[function(e){return r[e]}];e=function(){return'\\w+'};c=1};while(c--)if(k[c])p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c]);return p}('h.i[\'1a\']=h.i[\'z\'];h.O(h.i,{y:\'D\',z:9(x,t,b,c,d){6 h.i[h.i.y](x,t,b,c,d)},17:9(x,t,b,c,d){6 c*(t/=d)*t+b},D:9(x,t,b,c,d){6-c*(t/=d)*(t-2)+b},13:9(x,t,b,c,d){e((t/=d/2)<1)6 c/2*t*t+b;6-c/2*((--t)*(t-2)-1)+b},X:9(x,t,b,c,d){6 c*(t/=d)*t*t+b},U:9(x,t,b,c,d){6 c*((t=t/d-1)*t*t+1)+b},R:9(x,t,b,c,d){e((t/=d/2)<1)6 c/2*t*t*t+b;6 c/2*((t-=2)*t*t+2)+b},N:9(x,t,b,c,d){6 c*(t/=d)*t*t*t+b},M:9(x,t,b,c,d){6-c*((t=t/d-1)*t*t*t-1)+b},L:9(x,t,b,c,d){e((t/=d/2)<1)6 c/2*t*t*t*t+b;6-c/2*((t-=2)*t*t*t-2)+b},K:9(x,t,b,c,d){6 c*(t/=d)*t*t*t*t+b},J:9(x,t,b,c,d){6 c*((t=t/d-1)*t*t*t*t+1)+b},I:9(x,t,b,c,d){e((t/=d/2)<1)6 c/2*t*t*t*t*t+b;6 c/2*((t-=2)*t*t*t*t+2)+b},G:9(x,t,b,c,d){6-c*8.C(t/d*(8.g/2))+c+b},15:9(x,t,b,c,d){6 c*8.n(t/d*(8.g/2))+b},12:9(x,t,b,c,d){6-c/2*(8.C(8.g*t/d)-1)+b},Z:9(x,t,b,c,d){6(t==0)?b:c*8.j(2,10*(t/d-1))+b},Y:9(x,t,b,c,d){6(t==d)?b+c:c*(-8.j(2,-10*t/d)+1)+b},W:9(x,t,b,c,d){e(t==0)6 b;e(t==d)6 b+c;e((t/=d/2)<1)6 c/2*8.j(2,10*(t-1))+b;6 c/2*(-8.j(2,-10*--t)+2)+b},V:9(x,t,b,c,d){6-c*(8.o(1-(t/=d)*t)-1)+b},S:9(x,t,b,c,d){6 c*8.o(1-(t=t/d-1)*t)+b},Q:9(x,t,b,c,d){e((t/=d/2)<1)6-c/2*(8.o(1-t*t)-1)+b;6 c/2*(8.o(1-(t-=2)*t)+1)+b},P:9(x,t,b,c,d){f s=1.l;f p=0;f a=c;e(t==0)6 b;e((t/=d)==1)6 b+c;e(!p)p=d*.3;e(a<8.w(c)){a=c;f s=p/4}m f s=p/(2*8.g)*8.r(c/a);6-(a*8.j(2,10*(t-=1))*8.n((t*d-s)*(2*8.g)/p))+b},H:9(x,t,b,c,d){f s=1.l;f p=0;f a=c;e(t==0)6 b;e((t/=d)==1)6 b+c;e(!p)p=d*.3;e(a<8.w(c)){a=c;f s=p/4}m f s=p/(2*8.g)*8.r(c/a);6 a*8.j(2,-10*t)*8.n((t*d-s)*(2*8.g)/p)+c+b},T:9(x,t,b,c,d){f s=1.l;f p=0;f a=c;e(t==0)6 b;e((t/=d/2)==2)6 b+c;e(!p)p=d*(.3*1.5);e(a<8.w(c)){a=c;f s=p/4}m f s=p/(2*8.g)*8.r(c/a);e(t<1)6-.5*(a*8.j(2,10*(t-=1))*8.n((t*d-s)*(2*8.g)/p))+b;6 a*8.j(2,-10*(t-=1))*8.n((t*d-s)*(2*8.g)/p)*.5+c+b},F:9(x,t,b,c,d,s){e(s==u)s=1.l;6 c*(t/=d)*t*((s+1)*t-s)+b},E:9(x,t,b,c,d,s){e(s==u)s=1.l;6 c*((t=t/d-1)*t*((s+1)*t+s)+1)+b},16:9(x,t,b,c,d,s){e(s==u)s=1.l;e((t/=d/2)<1)6 c/2*(t*t*(((s*=(1.B))+1)*t-s))+b;6 c/2*((t-=2)*t*(((s*=(1.B))+1)*t+s)+2)+b},A:9(x,t,b,c,d){6 c-h.i.v(x,d-t,0,c,d)+b},v:9(x,t,b,c,d){e((t/=d)<(1/2.k)){6 c*(7.q*t*t)+b}m e(t<(2/2.k)){6 c*(7.q*(t-=(1.5/2.k))*t+.k)+b}m e(t<(2.5/2.k)){6 c*(7.q*(t-=(2.14/2.k))*t+.11)+b}m{6 c*(7.q*(t-=(2.18/2.k))*t+.19)+b}},1b:9(x,t,b,c,d){e(t<d/2)6 h.i.A(x,t*2,0,c,d)*.5+b;6 h.i.v(x,t*2-d,0,c,d)*.5+c*.5+b}});',62,74,'||||||return||Math|function|||||if|var|PI|jQuery|easing|pow|75|70158|else|sin|sqrt||5625|asin|||undefined|easeOutBounce|abs||def|swing|easeInBounce|525|cos|easeOutQuad|easeOutBack|easeInBack|easeInSine|easeOutElastic|easeInOutQuint|easeOutQuint|easeInQuint|easeInOutQuart|easeOutQuart|easeInQuart|extend|easeInElastic|easeInOutCirc|easeInOutCubic|easeOutCirc|easeInOutElastic|easeOutCubic|easeInCirc|easeInOutExpo|easeInCubic|easeOutExpo|easeInExpo||9375|easeInOutSine|easeInOutQuad|25|easeOutSine|easeInOutBack|easeInQuad|625|984375|jswing|easeInOutBounce'.split('|'),0,{}))

/*
 *
 * TERMS OF USE - EASING EQUATIONS
 * 
 * Open source under the BSD License. 
 * 
 * Copyright © 2001 Robert Penner
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list of 
 * conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or other materials 
 * provided with the distribution.
 * 
 * Neither the name of the author nor the names of contributors may be used to endorse 
 * or promote products derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 */





/*
 * jQuery Easing Compatibility v1 - http://gsgd.co.uk/sandbox/jquery.easing.php
 *
 * Adds compatibility for applications that use the pre 1.2 easing names
 *
 * Copyright (c) 2007 George Smith
 * Licensed under the MIT License:
 *   http://www.opensource.org/licenses/mit-license.php
 */
eval(function(p,a,c,k,e,d){e=function(c){return(c<a?"":e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--){d[e(c)]=k[c]||e(c)}k=[function(e){return d[e]}];e=function(){return'\\w+'};c=1};while(c--){if(k[c]){p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c])}}return p}('0.C(0.1,{7:2(x,t,b,c,d){3 0.1.D(x,t,b,c,d)},5:2(x,t,b,c,d){3 0.1.6(x,t,b,c,d)},h:2(x,t,b,c,d){3 0.1.B(x,t,b,c,d)},A:2(x,t,b,c,d){3 0.1.m(x,t,b,c,d)},y:2(x,t,b,c,d){3 0.1.w(x,t,b,c,d)},v:2(x,t,b,c,d){3 0.1.u(x,t,b,c,d)},s:2(x,t,b,c,d){3 0.1.r(x,t,b,c,d)},q:2(x,t,b,c,d){3 0.1.p(x,t,b,c,d)},o:2(x,t,b,c,d){3 0.1.n(x,t,b,c,d)},8:2(x,t,b,c,d){3 0.1.l(x,t,b,c,d)},g:2(x,t,b,c,d){3 0.1.j(x,t,b,c,d)},i:2(x,t,b,c,d){3 0.1.k(x,t,b,c,d)},z:2(x,t,b,c,d){3 0.1.f(x,t,b,c,d)},e:2(x,t,b,c,d){3 0.1.a(x,t,b,c,d)},9:2(x,t,b,c,d){3 0.1.4(x,t,b,c,d)}});',40,40,'jQuery|easing|function|return|easeInOutBack|easeOut|easeOutQuad|easeIn|elasin|backinout|easeOutBack||||backout|easeInBack|elasout|easeInOut|elasinout|easeOutElastic|easeInOutElastic|easeInElastic|easeInExpo|easeInOutBounce|bounceinout|easeOutBounce|bounceout|easeInBounce|bouncein||easeInOutExpo|expoinout|easeOutExpo||expoout|backin|expoin|easeInOutQuad|extend|easeInQuad'.split('|'),0,{}))



/*
	jQuery Coda-Slider v1.1 - http://www.ndoherty.com/coda-slider
	
	Copyright (c) 2007 Niall Doherty
*/
eval(function(p,a,c,k,e,d){e=function(c){return(c<a?"":e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--){d[e(c)]=k[c]||e(c)}k=[function(e){return d[e]}];e=function(){return'\\w+'};c=1};while(c--){if(k[c]){p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c])}}return p}('3(d(){3("4.T").1s("<p r=\'O\'>16...<1t /><18 19=\'1a/11-1b.1c\' 1d=\'O...\'/ ></p>")});b j=0;3.1e.1f=d(f){f=3.1g({G:"1h",E:1i,1j:Q},f);P 6.w(d(){b o=3(6);o.7("p.O").1k();o.q("T").l("1l");b m=o.7("4.I").C();b k=o.7("4.I").1m();b U=m*k;o.7("4.t").K("C",U);b N=k*2;F(h.g&&D(h.g.s(1))<=k){b 9=D(h.g.s(1));b e=-(m*(9-1));3(6).7("4.t").K({H:e})}B{b 9=1};o.w(d(i){3(6).W("<4 r=\'J\' M=\'J"+j+"\'><a A=\'#\'>1n</a><\\/4>");3(6).1o("<4 r=\'L\' M=\'L"+j+"\'><a A=\'#\'>1q</a><\\/4>");3(6).W("<4 r=\'c\' M=\'c"+j+"\'><v><\\/v><\\/4>");3(6).7("4.I").w(d(n){3("4#c"+j+" v").X("<x r=\'Z"+(n+1)+"\'><a A=\'#"+(n+1)+"\'>"+3(6).S("10")+"<\\/a><\\/x>")});3("4#c"+j+" a").w(d(z){N+=3(6).5().C();3(6).12("u",d(){3(6).l("8").5().5().7("a").13(3(6)).q("8");b e=-(m*z);9=z+1;3(6).5().5().5().V().7("4.t").R({H:e},f.E,f.G)})});3("4#J"+j+" a").u(d(){F(9==1){b e=-(m*(k-1));9=k;3(6).5().5().7("4.c a.8").q("8").5().5().7("x:14 a").l("8")}B{9-=1;b e=-(m*(9-1));3(6).5().5().7("4.c a.8").q("8").5().15().7("a").l("8")};3(6).5().5().7("4.t").R({H:e},f.E,f.G);h.g=9;P Q});3("4#L"+j+" a").u(d(){F(9==k){b e=0;9=1;3(6).5().5().7("4.c a.8").q("8").5().5().7("a:y(0)").l("8")}B{b e=-(m*9);9+=1;3(6).5().5().7("4.c a.8").q("8").5().V().7("a").l("8")};3(6).5().5().7("4.t").R({H:e},f.E,f.G);h.g=9;P Q});3("a.1p-1r").u(d(){3(6).Y().7(".c v x a:y("+(D(3(6).S("A").s(1))-1)+")").17(\'u\')});3("4#c"+j).K("C",N);F(h.g&&D(h.g.s(1))<=k){3("4#c"+j+" a:y("+(h.g.s(1)-1)+")").l("8")}B{3("4#c"+j+" a:y(0)").l("8")}});j++})};',62,92,'|||jQuery|div|parent|this|find|current|cPanel||var|stripNav|function|cnt|settings|hash|location|||panelCount|addClass|panelWidth||container||removeClass|class|slice|panelContainer|click|ul|each|li|eq||href|else|width|parseInt|easeTime|if|easeFunc|left|panel|stripNavL|css|stripNavR|id|navWidth|loading|return|false|animate|attr|csw|stripViewerWidth|next|before|append|parents|tab|title|ajax|bind|not|last|prev|Loading|trigger|img|src|images|loader|gif|alt|fn|codaSlider|extend|expoinout|750|toolTip|remove|stripViewer|size|Left|after|cross|Right|link|prepend|br'.split('|'),0,{}))



    var theInt = null;
    var $crosslink, $navthumb;
    var curclicked = 0;

    theInterval = function(cur) {
        clearInterval(theInt);

        if (typeof cur != 'undefined')
            curclicked = cur;

        $crosslink.removeClass("active-thumb");
        $navthumb.eq(curclicked).parent().addClass("active-thumb");
        $(".stripNav ul li a").eq(curclicked).trigger('click');

        theInt = setInterval(function() {
            $crosslink.removeClass("active-thumb");
            $navthumb.eq(curclicked).parent().addClass("active-thumb");
            $(".stripNav ul li a").eq(curclicked).trigger('click');
            curclicked++;
            if (4 == curclicked)
                curclicked = 0;

        }, 4000);
    };

    $(function() {

        $("#main-photo-slider").codaSlider();

        $navthumb = $("#movers-row a span");
        $crosslink = $(".cross-link");

        $navthumb
                .click(function() {
            var $this = $(this);
            theInterval($this.parent().attr('href').slice(1) - 1);
            return false;
        });

        theInterval();
		
		
		var linkz = document.links;

		var i = 0;

		for (i =0; i<linkz.length; i++)
		{

      		 if (linkz[i].href.indexOf('#')>0){

      		 var index = linkz[i].href.indexOf("#");

       		 var string =linkz[i].href.substring(index+1,linkz[i].href.length);


       		 if (!isNaN(string )){

           		if(string!==""){

           		linkz[i].href = "#"+string;

      		  }
		
        }

}

}
		
		
    });