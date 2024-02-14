#include <stdio.h>
#include <math.h>

// Define a structure to hold latitude, longitude, and country information
struct Location {
    double lat;
    double lon;
    const char *country;
};

int main() {
    // Define an array of structures to store latitude, longitude, and country information
    struct Location locations[] = {
        {42.546245, 1.601554, "Andorra"},
        {23.424076, 53.847818, "United Arab Emirates"},
	{33.93911,	67.709953,	"Afghanistan"},

	{17.060816,	-61.796428,	"Antigua and Barbuda"},

	{18.220554,	-63.068615,	"Anguilla"},

  {41.153332,	20.168331,	"Albania"},

 {40.069099,	45.038189,	"Armenia"},

 {12.226079,	-69.060087,	"Netherlands Antilles"},

 {-11.202692,	17.873887,	"Angola"},

 {-75.250973	-0.071389	Antarctica

 {-38.416097	-63.616672	Argentina

 {-14.270972	-170.132217	American Samoa



 {47.516231	14.550072	Austria

 {-25.274398	133.775136	Australia

 {12.52111	-69.968338	Aruba

 {40.143105	47.576927	Azerbaijan

 {43.915886	17.679076	Bosnia and Herzegovina

 {13.193887	-59.543198	Barbados

 {23.684994	90.356331	Bangladesh

 {50.503887	4.469936	Belgium

 {12.238333	-1.561593	Burkina Faso

 {42.733883	25.48583	Bulgaria

 {25.930414	50.637772	Bahrain

 {-3.373056	29.918886	Burundi

 {9.30769	2.315834	Benin

 {32.321384	-64.75737	Bermuda

 {4.535277	114.727669	Brunei

 {-16.290154	-63.588653	Bolivia

 {-14.235004	-51.92528	Brazil

 {25.03428	-77.39628	Bahamas

 {27.514162	90.433601	Bhutan

 {-54.423199	3.413194	Bouvet Island

 {-22.328474	24.684866	Botswana

 {53.709807	27.953389	Belarus

 {17.189877	-88.49765	Belize

 {56.130366	-106.346771	Canada

 {-12.164165	96.870956	Cocos [Keeling] Islands

 {-4.038333	21.758664	Congo [DRC]

 {6.611111	20.939444	Central African Republic

-0.228021	15.827659	Congo [Republic]

46.818188	8.227512	Switzerland

7.539989	-5.54708	Côte d'Ivoire

-21.236736	-159.777671	Cook Islands

-35.675147	-71.542969	Chile

7.369722	12.354722	Cameroon

35.86166	104.195397	China

4.570868	-74.297333	Colombia

9.748917	-83.753428	Costa Rica

21.521757	-77.781167	Cuba

16.002082	-24.013197	Cape Verde

-10.447525	105.690449	Christmas Island

35.126413	33.429859	Cyprus

49.817492	15.472962	Czech Republic

51.165691	10.451526	Germany

11.825138	42.590275	Djibouti

56.26392	9.501785	Denmark

15.414999	-61.370976	Dominica

18.735693	-70.162651	Dominican Republic

28.033886	1.659626	Algeria

-1.831239	-78.183406	Ecuador

58.595272	25.013607	Estonia

26.820553	30.802498	Egypt

24.215527	-12.885834	Western Sahara

15.179384	39.782334	Eritrea

40.463667	-3.74922	Spain

9.145	40.489673	Ethiopia

61.92411	25.748151	Finland

-16.578193	179.414413	Fiji

-51.796253	-59.523613	Falkland Islands [Islas Malvinas]

7.425554	150.550812	Micronesia

61.892635	-6.911806	Faroe Islands

46.227638	2.213749	France

-0.803689	11.609444	Gabon

55.378051	-3.435973	United Kingdom

12.262776	-61.604171	Grenada

42.315407	43.356892	Georgia

3.933889	-53.125782	French Guiana

49.465691	-2.585278	Guernsey

7.946527	-1.023194	Ghana

36.137741	-5.345374	Gibraltar

71.706936	-42.604303	Greenland

13.443182	-15.310139	Gambia

9.945587	-9.696645	Guinea

16.995971	-62.067641	Guadeloupe

1.650801	10.267895	Equatorial Guinea

39.074208	21.824312	Greece

-54.429579	-36.587909	South Georgia and the South Sandwich Islands

15.783471	-90.230759	Guatemala

13.444304	144.793731	Guam

11.803749	-15.180413	Guinea-Bissau

4.860416	-58.93018	Guyana

31.354676	34.308825	Gaza Strip

22.396428	114.109497	Hong Kong

-53.08181	73.504158	Heard Island and McDonald Islands

15.199999	-86.241905	Honduras

45.1	15.2	Croatia

18.971187	-72.285215	Haiti

47.162494	19.503304	Hungary

-0.789275	113.921327	Indonesia

53.41291	-8.24389	Ireland

31.046051	34.851612	Israel

54.236107	-4.548056	Isle of Man

20.593684	78.96288	India

-6.343194	71.876519	British Indian Ocean Territory

33.223191	43.679291	Iraq

32.427908	53.688046	Iran

64.963051	-19.020835	Iceland

41.87194	12.56738	Italy

49.214439	-2.13125	Jersey

18.109581	-77.297508	Jamaica

30.585164	36.238414	Jordan

36.204824	138.252924	Japan

-0.023559	37.906193	Kenya

41.20438	74.766098	Kyrgyzstan

12.565679	104.990963	Cambodia

-3.370417	-168.734039	Kiribati

-11.875001	43.872219	Comoros

17.357822	-62.782998	Saint Kitts and Nevis

40.339852	127.510093	North Korea

35.907757	127.766922	South Korea

29.31166	47.481766	Kuwait

19.513469	-80.566956	Cayman Islands

48.019573	66.923684	Kazakhstan

19.85627	102.495496	Laos

33.854721	35.862285	Lebanon

13.909444	-60.978893	Saint Lucia

47.166	9.555373	Liechtenstein

7.873054	80.771797	Sri Lanka

6.428055	-9.429499	Liberia

-29.609988	28.233608	Lesotho

55.169438	23.881275	Lithuania

49.815273	6.129583	Luxembourg

56.879635	24.603189	Latvia

26.3351	17.228331	Libya

31.791702	-7.09262	Morocco

43.750298	7.412841	Monaco

47.411631	28.369885	Moldova

42.708678	19.37439	Montenegro

-18.766947	46.869107	Madagascar

7.131474	171.184478	Marshall Islands

41.608635	21.745275	Macedonia [FYROM]

17.570692	-3.996166	Mali

21.913965	95.956223	Myanmar [Burma]

46.862496	103.846656	Mongolia

22.198745	113.543873	Macau

17.33083	145.38469	Northern Mariana Islands

14.641528	-61.024174	Martinique

21.00789	-10.940835	Mauritania

16.742498	-62.187366	Montserrat

35.937496	14.375416	Malta

-20.348404	57.552152	Mauritius

3.202778	73.22068	Maldives

-13.254308	34.301525	Malawi

23.634501	-102.552784	Mexico

4.210484	101.975766	Malaysia

-18.665695	35.529562	Mozambique

-22.95764	18.49041	Namibia

-20.904305	165.618042	New Caledonia

17.607789	8.081666	Niger

-29.040835	167.954712	Norfolk Island

9.081999	8.675277	Nigeria

12.865416	-85.207229	Nicaragua

52.132633	5.291266	Netherlands

60.472024	8.468946	Norway

28.394857	84.124008	Nepal

-0.522778	166.931503	Nauru

-19.054445	-169.867233	Niue

-40.900557	174.885971	New Zealand

21.512583	55.923255	Oman

8.537981	-80.782127	Panama

-9.189967	-75.015152	Peru

-17.679742	-149.406843	French Polynesia

-6.314993	143.95555	Papua New Guinea

12.879721	121.774017	Philippines

30.375321	69.345116	Pakistan

51.919438	19.145136	Poland

46.941936	-56.27111	Saint Pierre and Miquelon

-24.703615	-127.439308	Pitcairn Islands

18.220833	-66.590149	Puerto Rico

31.952162	35.233154	Palestinian Territories

39.399872	-8.224454	Portugal

7.51498	134.58252	Palau

-23.442503	-58.443832	Paraguay

25.354826	51.183884	Qatar

-21.115141	55.536384	Réunion

45.943161	24.96676	Romania

44.016521	21.005859	Serbia

61.52401	105.318756	Russia

-1.940278	29.873888	Rwanda

23.885942	45.079162	Saudi Arabia

-9.64571	160.156194	Solomon Islands

-4.679574	55.491977	Seychelles

12.862807	30.217636	Sudan

60.128161	18.643501	Sweden

1.352083	103.819836	Singapore

-24.143474	-10.030696	Saint Helena

46.151241	14.995463	Slovenia

77.553604	23.670272	Svalbard and Jan Mayen

48.669026	19.699024	Slovakia

8.460555	-11.779889	Sierra Leone

43.94236	12.457777	San Marino

14.497401	-14.452362	Senegal

5.152149	46.199616	Somalia

3.919305	-56.027783	Suriname

0.18636	6.613081	São Tomé and Príncipe

13.794185	-88.89653	El Salvador

34.802075	38.996815	Syria

-26.522503	31.465866	Swaziland

21.694025	-71.797928	Turks and Caicos Islands

15.454166	18.732207	Chad

-49.280366	69.348557	French Southern Territories

8.619543	0.824782	Togo

15.870032	100.992541	Thailand

38.861034	71.276093	Tajikistan

-8.967363	-171.855881	Tokelau

-8.874217	125.727539	Timor-Leste

{38.969719,	59.556278,	"Turkmenistan"},

{33.886917,	9.537499,	"Tunisia"},

{-21.178986,	-175.198242,	"Tonga"},

{38.963745,	35.243322,	"Turkey"},

{10.691803,	-61.222503,	"Trinidad and Tobago"},

{-7.109535,	177.64933,	"Tuvalu"},

{23.69781,	120.960515,	"Taiwan"},

{-6.369028,	34.888822,	"Tanzania"},

{48.379433,	31.16558,	"Ukraine"},

{1.373333,	32.290275,	"UgandaU.S. Minor Outlying Islands"},

{37.09024,	-95.712891,	"United States"},

{-32.522779,	-55.765835,	"Uruguay"},

{41.377491,	64.585262,	"Uzbekistan"},

{41.902916,	12.453389,	"Vatican City"},

{12.984305,	-61.287228,	"Saint Vincent and the Grenadines"},

{6.42375,	-66.58973,	"Venezuela"},

{18.420695,	-64.639968,	"British Virgin Islands"},

{18.335765,	-64.896335,	"U.S. Virgin Islands"},

{14.058324,	108.277199,	"Vietnam"},

{-15.376706,	166.959158,	"Vanuatu"},

{-13.768752,	-177.156097,	"Wallis and Futuna"},

{-13.759029,	-172.104629,	"Samoa"},

{42.602636,	20.902977,	"Kosovo"},

{15.552727,	48.516388,	"Yemen"},

{-12.8275,	45.166244,	"Mayotte"},

{-30.559482,	22.937506,	"South Africa"},

{-13.133897,	27.849332,	"Zambia"},

{-19.015438,	29.154857,	"Zimbabwe"},


        // Add more locations here
    };

    double lat, lon;

    printf("Enter the latitude: ");
    scanf("%lf", &lat);

    printf("Enter the longitude: ");
    scanf("%lf", &lon);

    int found = 0;

    // Loop through the array to find a matching location
    for (int i = 0; i < sizeof(locations) / sizeof(locations[0]); i++) {
        if (fabs(locations[i].lat - lat) < 1e-6 && fabs(locations[i].lon - lon) < 1e-6) {
            printf("The country is %s\n", locations[i].country);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Country not identified for the given coordinates.\n");
    }

    return 0;
}

