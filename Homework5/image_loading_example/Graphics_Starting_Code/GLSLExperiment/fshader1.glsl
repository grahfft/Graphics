#version 150

in  vec2 texCoord;
uniform int fragFilter;

out vec4 fColor;

uniform sampler2D texture;
const vec3 sRGB = vec3( 0.2125, 0.7154, 0.0721);

void OriginalImage()
{
	fColor = texture2D( texture, texCoord );
}

void GrayScaleImage()
{
	vec3 irgb = texture2D( texture, texCoord ).rgb;
	float luminance = dot(irgb, sRGB);
    fColor = vec4( luminance, luminance, luminance, 1 );
}

void NegativeImage()
{
	vec3 irgb = texture2D( texture, texCoord ).rgb;
	fColor = vec4( 1 - irgb.r, 1 - irgb.g, 1 - irgb.b, 1);
}

void EdgeDetectionImage()
{
	ivec2 ires = textureSize( texture, 0 );
	float ResS = float( ires.s );
	float ResT = float( ires.t );
	vec3 irgb = texture2D( texture, texCoord ).rgb;

	vec2 stp0 = vec2( 1/ResS, 0 );
	vec2 st0p = vec2( 0, 1/ResT );
	vec2 stpp = vec2( 1/ResS, 1/ResT );
	vec2 stpm = vec2( 1/ResS, -1/ResT );

	float i00 = dot( texture2D( texture, texCoord ).rgb, sRGB );

	float im1m1 = dot( texture2D( texture, texCoord - stpp ).rgb, sRGB );
	float ip1p1 = dot( texture2D( texture, texCoord + stpp ).rgb, sRGB );

	float im1p1 = dot( texture2D( texture, texCoord - stpm ).rgb, sRGB );
	float ip1m1 = dot( texture2D( texture, texCoord + stpm ).rgb, sRGB );

	float im10 = dot( texture2D( texture, texCoord - stp0 ).rgb, sRGB );
	float ip10 = dot( texture2D( texture, texCoord + stp0 ).rgb, sRGB );

	float i0m1 = dot( texture2D( texture, texCoord - st0p ).rgb, sRGB );
	float i0p1 = dot( texture2D( texture, texCoord + st0p ).rgb, sRGB );

	float h = -1.*im1p1-2.*i0p1-1.*ip1p1+1.*im1m1+2.*i0m1+1.*ip1m1;
	float v = -1.*im1m1-2.*im10-1.*im1p1+1.*ip1m1+2.*ip10+1.*ip1p1;

	float mag = length( vec2( h, v) );
	vec3 target = vec3( mag, mag, mag );

	float uT = 5.0;

	fColor = vec4( mix( irgb, target, 3.0), 1);
}

void EmbossImage()
{
	ivec2 ires = textureSize( texture, 0 );
	float ResS = float( ires.s );
	float ResT = float( ires.t );
	vec3 irgb = texture2D( texture, texCoord ).rgb;

	vec2 stp0 = vec2( 1/ResS, 0 );
	vec2 stpp = vec2( 1/ResS, 1/ResT );

	vec3 c00 = texture2D( texture, texCoord ).rgb;
	vec3 cp1p1 = texture2D( texture, texCoord + stpp ).rgb;

	vec3 diffs = c00 - cp1p1;
	float max = diffs.r;
	if( abs(diffs.g) > abs(max) ) max = diffs.g;
	if( abs(diffs.b) > abs(max) ) max = diffs.b;

	float gray = clamp( max + .5, 0, 1);
	fColor = vec4( gray, gray, gray, 1 );
}

void ToonRendering()
{
	float magThreshold = 1.0;
	float quantizeFactor = 10.0;
	float quantizeValue = 10.0;

	ivec2 ires = textureSize( texture, 0 );
	float ResS = float( ires.s );
	float ResT = float( ires.t );
	vec3 irgb = texture2D( texture, texCoord ).rgb;

	vec3 rgb = texture2D( texture, texCoord ).rgb;
	vec2 stp0 = vec2( 1/ResS, 0 );
	vec2 st0p = vec2( 0, 1/ResT );
	vec2 stpp = vec2( 1/ResS, 1/ResT );
	vec2 stpm = vec2( 1/ResS, -1/ResT );

	float i00 = dot( texture2D( texture, texCoord ).rgb, sRGB );

	float im1m1 = dot( texture2D( texture, texCoord - stpp ).rgb, sRGB );
	float ip1p1 = dot( texture2D( texture, texCoord + stpp ).rgb, sRGB );

	float im1p1 = dot( texture2D( texture, texCoord - stpm ).rgb, sRGB );
	float ip1m1 = dot( texture2D( texture, texCoord + stpm ).rgb, sRGB );

	float im10 = dot( texture2D( texture, texCoord - stp0 ).rgb, sRGB );
	float ip10 = dot( texture2D( texture, texCoord + stp0 ).rgb, sRGB );

	float i0m1 = dot( texture2D( texture, texCoord - st0p ).rgb, sRGB );
	float i0p1 = dot( texture2D( texture, texCoord + st0p ).rgb, sRGB );

	float h = -1.*im1p1-2.*i0p1-1.*ip1p1+1.*im1m1+2.*i0m1+1.*ip1m1;
	float v = -1.*im1m1-2.*im10-1.*im1p1+1.*ip1m1+2.*ip10+1.*ip1p1;

	float mag = length( vec2( h, v) );

	if( mag > magThreshold )
	{
		fColor = vec4( 0, 0, 0, 1);
	}
	else
	{
		rgb.rgb *= quantizeFactor;
		rgb.rgb += vec3( .5, .5, .5 );
		ivec3 intrgb = ivec3( rgb.r, rgb.g, rgb.b );
		rgb.rgb = vec3( intrgb ) / quantizeFactor;
		fColor = vec4( rgb, 1);
	}
}

void TwirlImage()
{
	float uD = 60;
	float uR = 1;

	ivec2 ires = textureSize( texture, 0 );
	float Res = float( ires.s );

	vec2 st = texCoord;
	float Radius = Res * uR;
	vec2 xy = Res * st;

	vec2 dxy = xy - Res/2;
	float r = length( dxy );
	float beta = atan( dxy.y, dxy.x ) + radians(uD) * (Radius - r)/Radius;

	vec2 xy1 = xy;
	if( r <= Radius )
	{
		xy1 = Res/2 + r * vec2( cos(beta), sin(beta) );
	}
	st = xy1/Res;

	vec3 irgb = texture2D( texture, st ).rgb;
	fColor = vec4( irgb, 1 );
}

void main() 
{ 
    switch( fragFilter )
    {
    	case 0:
    		OriginalImage();
    		break;
		case 1:
			GrayScaleImage();
			break;
		case 2:
			NegativeImage();
			break;
		case 3:
			EdgeDetectionImage();
			break;
		case 4:
			EmbossImage();
			break;
		case 5:
			ToonRendering();
			break;
		case 6:
			TwirlImage();
			break;
    	default:
    		OriginalImage();
    		break;
    }
}