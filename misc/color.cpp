#include "color.h"

//QHash<QLatin1String, QLatin1String> Color::predefined = {
//'absolute zero' : '#0048BA'
//'acid' : '#B0BF1A'
//'aero' : '#7CB9E8'
//'air superiority blue' : '#72A0C1'
//'alabaster' : '#EDEAE0'
//'alice blue' : '#F0F8FF'
//'alloy orange' : '#C46210'
//'almond' : '#EFDECD'
//'amber' : '#FFBF00'
//'amethyst' : '#9966CC'
//'anti-flash white' : '#F2F3F4'
//'antique brass' : '#CD9575'
//'antique bronze' : '#665D1E'
//'antique fuchsia' : '#915C83'
//'antique ruby' : '#841B2D'
//'antique white' : '#FAEBD7'
//'ao' : '#008000'
//'apple green' : '#8DB600'
//'apricot' : '#FBCEB1'
//'aqua' : '#00FFFF'
//'aquamarine' : '#7FFFD4'
//'arctic lime' : '#D0FF14'
//'army green' : '#4B5320'
//'artichoke' : '#8F9779'
//'arylide yellow' : '#E9D66B'
//'ash gray' : '#B2BEB5'
//'asparagus' : '#87A96B'
//'atomic tangerine' : '#FF9966'
//'auburn' : '#A52A2A'
//'aureolin' : '#FDEE00'
//'avocado' : '#568203'
//'azure' : '#007FFF'
//'baby blue' : '#89CFF0'
//'baby blue eyes' : '#A1CAF1'
//'baby pink' : '#F4C2C2'
//'baker-miller pink' : '#FF91AF'
//'banana mania' : '#FAE7B5'
//'barbie pink' : '#E94196'
//'barn red' : '#7C0A02'
//'battleship grey' : '#848482'
//'beau blue' : '#BCD4E6'
//'beaver' : '#9F8170'
//'beige' : '#F5F5DC'
//'bdazzled blue' : '#2E5894'
//'big dip o’ruby' : '#9C2542'
//'bisque' : '#FFE4C4'
//'bistre' : '#3D2B1F'
//'bistre brown' : '#967117'
//'bitter lemon' : '#CAE00D'
//'bitter lime' : '#BFFF00'
//'bittersweet' : '#FE6F5E'
//'bittersweet shimmer' : '#BF4F51'
//'black' : '#000000'
//'black bean' : '#3D0C02'
//'black chocolate' : '#1B1811'
//'black coffee' : '#3B2F2F'
//'black coral' : '#54626F'
//'black olive' : '#3B3C36'
//'black shadows' : '#BFAFB2'
//'blanched almond' : '#FFEBCD'
//'blast-off bronze' : '#A57164'
//'bleu de france' : '#318CE7'
//'blizzard blue' : '#ACE5EE'
//'blond' : '#FAF0BE'
//'blood red' : '#660000'
//'blue' : '#0000FF'
//'blue bell' : '#A2A2D0'
//'blue-gray' : '#6699CC'
//'blue-green' : '#0D98BA'
//'blue jeans' : '#5DADEC'
//'blue sapphire' : '#126180'
//'blue-violet' : '#8A2BE2'
//'blue yonder' : '#5072A7'
//'bluetiful' : '#3C69E7'
//'blush' : '#DE5D83'
//'bole' : '#79443B'
//'bondi blue' : '#0095B6'
//'bone' : '#E3DAC9'
//'bottle green' : '#006A4E'
//'brandy' : '#87413F'
//'brick red' : '#CB4154'
//'bright green' : '#66FF00'
//'bright lilac' : '#D891EF'
//'bright maroon' : '#C32148'
//'bright navy blue' : '#1974D2'
//'bright pink' : '#FF007F'
//'bright yellow' : '#FFAA1D'
//'brilliant rose' : '#FF55A3'
//'brink pink' : '#FB607F'
//'british racing green' : '#004225'
//'bronze' : '#CD7F32'
//'brown' : '#88540B'
//'brown sugar' : '#AF6E4D'
//'brunswick green' : '#1B4D3E'
//'bubbles' : '#E7FEFF'
//'bud green' : '#7BB661'
//'buff' : '#F0DC82'
//'burgundy' : '#800020'
//'burlywood' : '#DEB887'
//'burnished brown' : '#A17A74'
//'burnt orange' : '#CC5500'
//'burnt sienna' : '#E97451'
//'burnt umber' : '#8A3324'
//'byzantine' : '#BD33A4'
//'byzantium' : '#702963'
//'cadet' : '#536872'
//'cadet blue' : '#5F9EA0'
//'cadet grey' : '#91A3B0'
//'cadmium green' : '#006B3C'
//'cadmium orange' : '#ED872D'
//'cadmium red' : '#E30022'
//'cadmium yellow' : '#FFF600'
//'café au lait' : '#A67B5B'
//'café noir' : '#4B3621'
//'cal poly pomona green' : '#1E4D2B'
//'cambridge blue' : '#A3C1AD'
//'camel' : '#C19A6B'
//'cameo pink' : '#EFBBCC'
//'canary' : '#FFFF99'
//'canary yellow' : '#FFEF00'
//'candy apple red' : '#FF0800'
//'candy pink' : '#E4717A'
//'capri' : '#00BFFF'
//'caput mortuum' : '#592720'
//'cardinal' : '#C41E3A'
//'caribbean green' : '#00CC99'
//'carmine' : '#960018'
//'carnation pink' : '#FFA6C9'
//'carnelian' : '#B31B1B'
//'carolina blue' : '#56A0D3'
//'carrot orange' : '#ED9121'
//'castleton green' : '#00563F'
//'catawba' : '#703642'
//'cedar chest' : '#C95A49'
//'celadon' : '#ACE1AF'
//'celadon blue' : '#007BA7'
//'celadon green' : '#2F847C'
//'celeste' : '#B2FFFF'
//'celtic blue' : '#246BCE'
//'cerise' : '#DE3163'
//'cerulean' : '#007BA7'
//'cerulean blue' : '#2A52BE'
//'cerulean frost' : '#6D9BC3'
//'cg blue' : '#007AA5'
//'cg red' : '#E03C31'
//'champagne' : '#F7E7CE'
//'champagne pink' : '#F1DDCF'
//'charcoal' : '#36454F'
//'charleston green' : '#232B2B'
//'charm pink' : '#E68FAC'
//'chartreuse' : '#DFFF00'
//'cherry blossom pink' : '#FFB7C5'
//'chestnut' : '#954535'
//'china pink' : '#DE6FA1'
//'china rose' : '#A8516E'
//'chinese red' : '#AA381E'
//'chinese violet' : '#856088'
//'chinese yellow' : '#FFB200'
//'chocolate' : '#7B3F00'
//'chrome yellow' : '#FFA700'
//'cinereous' : '#98817B'
//'cinnabar' : '#E34234'
//'cinnamon satin' : '#CD607E'
//'citrine' : '#E4D00A'
//'citron' : '#9FA91F'
//'claret' : '#7F1734'
//'cobalt blue' : '#0047AB'
//'cocoa brown' : '#D2691E'
//'coffee' : '#6F4E37'
//'columbia blue' : '#B9D9EB'
//'congo pink' : '#F88379'
//'cool grey' : '#8C92AC'
//'copper' : '#B87333'
//'copper penny' : '#AD6F69'
//'copper red' : '#CB6D51'
//'copper rose' : '#996666'
//'coquelicot' : '#FF3800'
//'coral' : '#FF7F50'
//'coral pink' : '#F88379'
//'cordovan' : '#893F45'
//'corn' : '#FBEC5D'
//'cornflower blue' : '#6495ED'
//'cornsilk' : '#FFF8DC'
//'cosmic cobalt' : '#2E2D88'
//'cosmic latte' : '#FFF8E7'
//'cosmos pink' : '#FEBCFF'
//'coyote brown' : '#81613C'
//'cotton candy' : '#FFBCD9'
//'cream' : '#FFFDD0'
//'crimson' : '#DC143C'
//'cultured' : '#F5F5F5'
//'cyan' : '#00FFFF'
//'cyber grape' : '#58427C'
//'cyber yellow' : '#FFD300'
//'cyclamen' : '#F56FA1'
//'dark blue-gray' : '#666699'
//'dark brown' : '#654321'
//'dark byzantium' : '#5D3954'
//'dark cornflower blue' : '#26428B'
//'dark cyan' : '#008B8B'
//'dark electric blue' : '#536878'
//'dark goldenrod' : '#B8860B'
//'dark green' : '#013220'
//'dark jungle green' : '#1A2421'
//'dark khaki' : '#BDB76B'
//'dark lava' : '#483C32'
//'dark liver' : '#534B4F'
//'dark magenta' : '#8B008B'
//'dark medium gray' : '#A9A9A9'
//'dark moss green' : '#4A5D23'
//'dark olive green' : '#556B2F'
//'dark orange' : '#FF8C00'
//'dark orchid' : '#9932CC'
//'dark pastel green' : '#03C03C'
//'dark purple' : '#301934'
//'dark red' : '#8B0000'
//'dark salmon' : '#E9967A'
//'dark sea green' : '#8FBC8F'
//'dark sienna' : '#3C1414'
//'dark sky blue' : '#8CBED6'
//'dark slate blue' : '#483D8B'
//'dark slate gray' : '#2F4F4F'
//'dark spring green' : '#177245'
//'dark turquoise' : '#00CED1'
//'dark violet' : '#9400D3'
//'dartmouth green' : '#00703C'
//'davys grey' : '#555555'
//'deep cerise' : '#DA3287'
//'deep champagne' : '#FAD6A5'
//'deep chestnut' : '#B94E48'
//'deep fuchsia' : '#C154C1'
//'deep jungle green' : '#004B49'
//'deep pink' : '#FF1493'
//'deep saffron' : '#FF9933'
//'deep sky blue' : '#00BFFF'
//'deep space sparkle' : '#4A646C'
//'deep taupe' : '#7E5E60'
//'denim' : '#1560BD'
//'denim blue' : '#2243B6'
//'desert' : '#C19A6B'
//'desert sand' : '#EDC9AF'
//'dim gray' : '#696969'
//'dodger blue' : '#1E90FF'
//'dogwood rose' : '#D71868'
//'drab' : '#967117'
//'duke blue' : '#00009C'
//'dutch white' : '#EFDFBB'
//'earth yellow' : '#E1A95F'
//'ebony' : '#555D50'
//'ecru' : '#C2B280'
//'eerie black' : '#1B1B1B'
//'eggplant' : '#614051'
//'eggshell' : '#F0EAD6'
//'egyptian blue' : '#1034A6'
//'electric blue' : '#7DF9FF'
//'electric green' : '#00FF00'
//'electric indigo' : '#6F00FF'
//'electric lime' : '#CCFF00'
//'electric purple' : '#BF00FF'
//'electric violet' : '#8F00FF'
//'emerald' : '#50C878'
//'eminence' : '#6C3082'
//'english green' : '#1B4D3E'
//'english lavender' : '#B48395'
//'english red' : '#AB4B52'
//'english vermillion' : '#CC474B'
//'english violet' : '#563C5C'
//'erin' : '#00FF40'
//'eton blue' : '#96C8A2'
//'fallow' : '#C19A6B'
//'falu red' : '#801818'
//'fandango' : '#B53389'
//'fandango pink' : '#DE5285'
//'fashion fuchsia' : '#F400A1'
//'fawn' : '#E5AA70'
//'feldgrau' : '#4D5D53'
//'fern green' : '#4F7942'
//'field drab' : '#6C541E'
//'fiery rose' : '#FF5470'
//'firebrick' : '#B22222'
//'fire engine red' : '#CE2029'
//'fire opal' : '#E95C4B'
//'flame' : '#E25822'
//'flavescent' : '#F7E98E'
//'flax' : '#EEDC82'
//'flesh' : '#FFE9D1'
//'flirt' : '#A2006D'
//'floral white' : '#FFFAF0'
//'fluorescent blue' : '#15F4EE'
//'forest green' : '#228B22'
//'french beige' : '#A67B5B'
//'french bistre' : '#856D4D'
//'french blue' : '#0072BB'
//'french fuchsia' : '#FD3F92'
//'french lilac' : '#86608E'
//'french lime' : '#9EFD38'
//'french mauve' : '#D473D4'
//'french pink' : '#FD6C9E'
//'french raspberry' : '#C72C48'
//'french rose' : '#F64A8A'
//'french sky blue' : '#77B5FE'
//'french violet' : '#8806CE'
//'frostbite' : '#E936A7'
//'fuchsia' : '#FF00FF'
//'fuchsia purple' : '#CC397B'
//'fuchsia rose' : '#C74375'
//'fulvous' : '#E48400'
//'fuzzy wuzzy' : '#CC6666'
//'gainsboro' : '#DCDCDC'
//'gamboge' : '#E49B0F'
//'generic viridian' : '#007F66'
//'ghost white' : '#F8F8FF'
//'glaucous' : '#6082B6'
//'glossy grape' : '#AB92B3'
//'go green' : '#00AB66'
//'gold' : '#A57C00'
//'gold fusion' : '#85754E'
//'golden brown' : '#996515'
//'golden poppy' : '#FCC200'
//'golden yellow' : '#FFDF00'
//'goldenrod' : '#DAA520'
//'granite gray' : '#676767'
//'granny smith apple' : '#A8E4A0'
//'gray' : '#BEBEBE'
//'green' : '#00FF00'
//'green-blue' : '#1164B4'
//'green-cyan' : '#009966'
//'green lizard' : '#A7F432'
//'green sheen' : '#6EAEA1'
//'green-yellow' : '#ADFF2F'
//'grullo' : '#A99A86'
//'gunmetal' : '#2a3439'
//'han blue' : '#446CCF'
//'han purple' : '#5218FA'
//'hansa yellow' : '#E9D66B'
//'harlequin' : '#3FFF00'
//'harvest gold' : '#DA9100'
//'heat wave' : '#FF7A00'
//'heather grey' : 'custom'
//'heliotrope' : '#DF73FF'
//'heliotrope gray' : '#AA98A9'
//'hollywood cerise' : '#F400A1'
//'honeydew' : '#F0FFF0'
//'honolulu blue' : '#006DB0'
//'hookers green' : '#49796B'
//'hot magenta' : '#FF1DCE'
//'hot pink' : '#FF69B4'
//'hunter green' : '#355E3B'
//'iceberg' : '#71A6D2'
//'icterine' : '#FCF75E'
//'illuminating emerald' : '#319177'
//'imperial red' : '#ED2939'
//'inchworm' : '#B2EC5D'
//'independence' : '#4C516D'
//'india green' : '#138808'
//'indian red' : '#CD5C5C'
//'indian yellow' : '#E3A857'
//'indigo' : '#4B0082'
//'indigo blue' : '#00416A'
//'indigo dye' : '#091F92'
//'international klein blue' : '#002FA7'
//'international orange' : '#FF4F00'
//'iris' : '#5A4FCF'
//'irresistible' : '#B3446C'
//'isabelline' : '#F4F0EC'
//'islamic green' : '#009000'
//'italian sky blue' : '#B2FFFF'
//'ivory' : '#FFFFF0'
//'jade' : '#00A86B'
//'jasmine' : '#F8DE7E'
//'jazzberry jam' : '#A50B5E'
//'jet' : '#343434'
//'jonquil' : '#F4CA16'
//'june bud' : '#BDDA57'
//'jungle green' : '#29AB87'
//'kelly green' : '#4CBB17'
//'keppel' : '#3AB09E'
//'key lime' : '#E8F48C'
//'khaki' : '#C3B091'
//'kobe' : '#882D17'
//'kobi' : '#E79FC4'
//'kobicha' : '#6B4423'
//'kombu green' : '#354230'
//'ksu purple' : '#512888'
//'languid lavender' : '#D6CADD'
//'lapis lazuli' : '#26619C'
//'laser lemon' : '#FFFF66'
//'laurel green' : '#A9BA9D'
//'lava' : '#CF1020'
//'lavender' : '#E6E6FA'
//'lavender blue' : '#CCCCFF'
//'lavender blush' : '#FFF0F5'
//'lavender gray' : '#C4C3D0'
//'lavender magenta' : '#EE82EE'
//'lawn green' : '#7CFC00'
//'lemon' : '#FFF700'
//'lemon chiffon' : '#FFFACD'
//'lemon curry' : '#CCA01D'
//'lemon glacier' : '#FDFF00'
//'lemon meringue' : '#F6EABE'
//'lemon yellow' : '#FFF44F'
//'liberty' : '#545AA7'
//'light blue' : '#ADD8E6'
//'light coral' : '#F08080'
//'light cornflower blue' : '#93CCEA'
//'light cyan' : '#E0FFFF'
//'light french beige' : '#C8AD7F'
//'light goldenrod yellow' : '#FAFAD2'
//'light gray' : '#D3D3D3'
//'light green' : '#90EE90'
//'light orange' : '#FED8B1'
//'light periwinkle' : '#C5CBE1'
//'light pink' : '#FFB6C1'
//'light salmon' : '#FFA07A'
//'light sea green' : '#20B2AA'
//'light sky blue' : '#87CEFA'
//'light slate gray' : '#778899'
//'light steel blue' : '#B0C4DE'
//'light yellow' : '#FFFFE0'
//'lilac' : '#C8A2C8'
//'lilac luster' : '#AE98AA'
//'lime' : '#00FF00'
//'lime green' : '#32CD32'
//'lincoln green' : '#195905'
//'linen' : '#FAF0E6'
//'lion' : '#C19A6B'
//'liseran purple' : '#DE6FA1'
//'little boy blue' : '#6CA0DC'
//'liver' : '#674C47'
//'liver chestnut' : '#987456'
//'livid' : '#6699CC'
//'macaroni and cheese' : '#FFBD88'
//'madder lake' : '#CC3336'
//'magenta' : '#FF00FF'
//'magenta haze' : '#9F4576'
//'magic mint' : '#AAF0D1'
//'magnolia' : '#F8F4FF'
//'mahogany' : '#C04000'
//'maize' : '#FBEC5D'
//'majorelle blue' : '#6050DC'
//'malachite' : '#0BDA51'
//'manatee' : '#979AAA'
//'mandarin' : '#F37A48'
//'mango' : '#FDBE02'
//'mango tango' : '#FF8243'
//'mantis' : '#74C365'
//'mardi gras' : '#880085'
//'marigold' : '#EAA221'
//'maroon' : '#800000'
//'mauve' : '#E0B0FF'
//'mauve taupe' : '#915F6D'
//'mauvelous' : '#EF98AA'
//'maximum blue' : '#47ABCC'
//'maximum blue green' : '#30BFBF'
//'maximum blue purple' : '#ACACE6'
//'maximum green' : '#5E8C31'
//'maximum green yellow' : '#D9E650'
//'maximum purple' : '#733380'
//'maximum red' : '#D92121'
//'maximum yellow' : '#FAFA37'
//'maximum yellow red' : '#F2BA49'
//'may green' : '#4C9141'
//'maya blue' : '#73C2FB'
//'medium aquamarine' : '#66DDAA'
//'medium blue' : '#0000CD'
//'medium candy apple red' : '#E2062C'
//'medium carmine' : '#AF4035'
//'medium champagne' : '#F3E5AB'
//'medium orchid' : '#BA55D3'
//'medium purple' : '#9370DB'
//'medium sea green' : '#3CB371'
//'medium slate blue' : '#7B68EE'
//'medium spring green' : '#00FA9A'
//'medium turquoise' : '#48D1CC'
//'medium violet-red' : '#C71585'
//'mellow apricot' : '#F8B878'
//'mellow yellow' : '#F8DE7E'
//'melancholy' : '#FDBCB4'
//'melon' : '#FEBAAD'
//'metallic gold' : '#D3AF37'
//'metallic seaweed' : '#0A7E8C'
//'metallic sunburst' : '#9C7C38'
//'mexican pink' : '#E4007C'
//'middle blue' : '#7ED4E6'
//'middle blue green' : '#8DD9CC'
//'middle blue purple' : '#8B72BE'
//'middle grey' : '#8B8680'
//'middle green' : '#4D8C57'
//'middle green yellow' : '#ACBF60'
//'middle purple' : '#D982B5'
//'middle red' : '#E58E73'
//'middle red purple' : '#A55353'
//'middle yellow' : '#FFEB00'
//'middle yellow red' : '#ECB176'
//'midnight' : '#702670'
//'midnight blue' : '#191970'
//'midnight green' : '#004953'
//'mikado yellow' : '#FFC40C'
//'mimi pink' : '#FFDAE9'
//'mindaro' : '#E3F988'
//'ming' : '#36747D'
//'minion yellow' : '#F5E050'
//'mint' : '#3EB489'
//'mint cream' : '#F5FFFA'
//'mint green' : '#98FF98'
//'misty moss' : '#BBB477'
//'misty rose' : '#FFE4E1'
//'mode beige' : '#967117'
//'morning blue' : '#8DA399'
//'moss green' : '#8A9A5B'
//'mountain meadow' : '#30BA8F'
//'mountbatten pink' : '#997A8D'
//'msu green' : '#18453B'
//'mulberry' : '#C54B8C'
//'mustard' : '#FFDB58'
//'myrtle green' : '#317873'
//'mystic' : '#D65282'
//'mystic maroon' : '#AD4379'
//'naples yellow' : '#FADA5E'
//'navajo white' : '#FFDEAD'
//'navy' : '#000080'
//'navy blue' : '#000080'
//'neon blue' : '#4666FF'
//'neon green' : '#39FF14'
//'new york pink' : '#D7837F'
//'nickel' : '#727472'
//'non-photo blue' : '#A4DDED'
//'nyanza' : '#E9FFDB'
//'ocean blue' : '#4F42B5'
//'ocean green' : '#48BF91'
//'ochre' : '#CC7722'
//'old burgundy' : '#43302E'
//'old gold' : '#CFB53B'
//'old lace' : '#FDF5E6'
//'old lavender' : '#796878'
//'old mauve' : '#673147'
//'old rose' : '#C08081'
//'old silver' : '#848482'
//'olive' : '#808000'
//'olive drab' : '#6B8E23'
//'olive green' : '#B5B35C'
//'olivine' : '#9AB973'
//'onyx' : '#353839'
//'opal' : '#A8C3BC'
//'opera mauve' : '#B784A7'
//'orange' : '#FF6600'
//'orange peel' : '#FF9F00'
//'orange-red' : '#FF681F'
//'orange soda' : '#FA5B3D'
//'orange-yellow' : '#F5BD1F'
//'orchid' : '#DA70D6'
//'orchid pink' : '#F2BDCD'
//'outer space' : '#2D383A'
//'outrageous orange' : '#FF6E4A'
//'oxblood' : '#800020'
//'oxford blue' : '#002147'
//'ou crimson red' : '#841617'
//'pacific blue' : '#1CA9C9'
//'pakistan green' : '#006600'
//'palatinate purple' : '#682860'
//'pale aqua' : '#BCD4E6'
//'pale cerulean' : '#9BC4E2'
//'pale pink' : '#FADADD'
//'pale purple' : '#FAE6FA'
//'pale silver' : '#C9C0BB'
//'pale spring bud' : '#ECEBBD'
//'pansy purple' : '#78184A'
//'paolo veronese green' : '#009B7D'
//'papaya whip' : '#FFEFD5'
//'paradise pink' : '#E63E62'
//'paris green' : '#50C878'
//'pastel pink' : '#DEA5A4'
//'patriarch' : '#800080'
//'paynes grey' : '#536878'
//'peach' : '#FFCBA4'
//'peach puff' : '#FFDAB9'
//'pear' : '#D1E231'
//'pearly purple' : '#B768A2'
//'periwinkle' : '#CCCCFF'
//'permanent geranium lake' : '#E12C2C'
//'persian blue' : '#1C39BB'
//'persian green' : '#00A693'
//'persian indigo' : '#32127A'
//'persian orange' : '#D99058'
//'persian pink' : '#F77FBE'
//'persian plum' : '#701C1C'
//'persian red' : '#CC3333'
//'persian rose' : '#FE28A2'
//'persimmon' : '#EC5800'
//'pewter blue' : '#8BA8B7'
//'phlox' : '#DF00FF'
//'phthalo blue' : '#000F89'
//'phthalo green' : '#123524'
//'picotee blue' : '#2E2787'
//'pictorial carmine' : '#C30B4E'
//'piggy pink' : '#FDDDE6'
//'pine green' : '#01796F'
//'pine tree' : '#2A2F23'
//'pink' : '#FFC0CB'
//'pink flamingo' : '#FC74FD'
//'pink lace' : '#FFDDF4'
//'pink lavender' : '#D8B2D1'
//'pink sherbet' : '#F78FA7'
//'pistachio' : '#93C572'
//'platinum' : '#E5E4E2'
//'plum' : '#8E4585'
//'plump purple' : '#5946B2'
//'polished pine' : '#5DA493'
//'pomp and power' : '#86608E'
//'popstar' : '#BE4F62'
//'portland orange' : '#FF5A36'
//'powder blue' : '#B0E0E6'
//'princeton orange' : '#F58025'
//'prune' : '#701C1C'
//'prussian blue' : '#003153'
//'psychedelic purple' : '#DF00FF'
//'puce' : '#CC8899'
//'pullman brown' : '#644117'
//'pumpkin' : '#FF7518'
//'purple' : '#6A0DAD'
//'purple mountain majesty' : '#9678B6'
//'purple navy' : '#4E5180'
//'purple pizzazz' : '#FE4EDA'
//'purple plum' : '#9C51B6'
//'purpureus' : '#9A4EAE'
//'queen blue' : '#436B95'
//'queen pink' : '#E8CCD7'
//'quick silver' : '#A6A6A6'
//'quinacridone magenta' : '#8E3A59'
//'radical red' : '#FF355E'
//'raisin black' : '#242124'
//'rajah' : '#FBAB60'
//'raspberry' : '#E30B5D'
//'raspberry glace' : '#915F6D'
//'raspberry rose' : '#B3446C'
//'raw sienna' : '#D68A59'
//'raw umber' : '#826644'
//'razzle dazzle rose' : '#FF33CC'
//'razzmatazz' : '#E3256B'
//'razzmic berry' : '#8D4E85'
//'rebecca purple' : '#663399'
//'red' : '#FF0000'
//'red-orange' : '#FF5349'
//'red-purple' : '#E40078'
//'red salsa' : '#FD3A4A'
//'red-violet' : '#C71585'
//'redwood' : '#A45A52'
//'resolution blue' : '#002387'
//'rhythm' : '#777696'
//'rich black' : '#004040'
//'rifle green' : '#444C38'
//'robin egg blue' : '#00CCCC'
//'rocket metallic' : '#8A7F80'
//'roman silver' : '#838996'
//'rose' : '#FF007F'
//'rose bonbon' : '#F9429E'
//'rose dust' : '#9E5E6F'
//'rose ebony' : '#674846'
//'rose madder' : '#E32636'
//'rose pink' : '#FF66CC'
//'rose quartz' : '#AA98A9'
//'rose red' : '#C21E56'
//'rose taupe' : '#905D5D'
//'rose vale' : '#AB4E52'
//'rosewood' : '#65000B'
//'rosso corsa' : '#D40000'
//'rosy brown' : '#BC8F8F'
//'royal blue' : '#002366' # 'royal' : '#002366'
//'royal purple' : '#7851A9'
//'royal yellow' : '#FADA5E'
//'ruber' : '#CE4676'
//'rubine red' : '#D10056'
//'ruby' : '#E0115F'
//'ruby red' : '#9B111E'
//'rufous' : '#A81C07'
//'russet' : '#80461B'
//'russian green' : '#679267'
//'russian violet' : '#32174D'
//'rust' : '#B7410E'
//'rusty red' : '#DA2C43'
//'sacramento state green' : '#043927'
//'saddle brown' : '#8B4513'
//'safety orange' : '#FF7800'
//'safety yellow' : '#EED202'
//'saffron' : '#F4C430'
//'sage' : '#BCB88A'
//'st. patricks blue' : '#23297A'
//'salmon' : '#FA8072'
//'salmon pink' : '#FF91A4'
//'sand' : '#C2B280'
//'sand dune' : '#967117'
//'sandy brown' : '#F4A460'
//'sap green' : '#507D2A'
//'sapphire' : '#0F52BA'
//'sapphire blue' : '#0067A5'
//'satin sheen gold' : '#CBA135'
//'scarlet' : '#FF2400'
//'schauss pink' : '#FF91AF'
//'school bus yellow' : '#FFD800'
//'screamin green' : '#66FF66'
//'sea green' : '#2E8B57'
//'seal brown' : '#59260B'
//'seashell' : '#FFF5EE'
//'selective yellow' : '#FFBA00'
//'sepia' : '#704214'
//'shadow' : '#8A795D'
//'shadow blue' : '#778BA5'
//'shamrock green' : '#009E60'
//'sheen green' : '#8FD400'
//'shimmering blush' : '#D98695'
//'shiny shamrock' : '#5FA778'
//'shocking pink' : '#FC0FC0'
//'sienna' : '#882D17'
//'silver' : '#C0C0C0'
//'silver chalice' : '#ACACAC'
//'silver pink' : '#C4AEAD'
//'silver sand' : '#BFC1C2'
//'sinopia' : '#CB410B'
//'sizzling red' : '#FF3855'
//'sizzling sunrise' : '#FFDB00'
//'skobeloff' : '#007474'
//'sky blue' : '#87CEEB'
//'sky magenta' : '#CF71AF'
//'slate blue' : '#6A5ACD'
//'slate gray' : '#708090'
//'slimy green' : '#299617'
//'smitten' : '#C84186'
//'smoky black' : '#100C08'
//'snow' : '#FFFAFA'
//'solid pink' : '#893843'
//'sonic silver' : '#757575'
//'space cadet' : '#1D2951'
//'spanish bistre' : '#807532'
//'spanish blue' : '#0070B8'
//'spanish carmine' : '#D10047'
//'spanish gray' : '#989898'
//'spanish green' : '#009150'
//'spanish orange' : '#E86100'
//'spanish pink' : '#F7BFBE'
//'spanish red' : '#E60026'
//'spanish sky blue' : '#00FFFF'
//'spanish violet' : '#4C2882'
//'spanish viridian' : '#007F5C'
//'spring bud' : '#A7FC00'
//'spring frost' : '#87FF2A'
//'spring green' : '#00FF7F'
//'star command blue' : '#007BB8'
//'steel blue' : '#4682B4'
//'steel pink' : '#CC33CC'
//'steel teal' : '#5F8A8B'
//'stil de grain yellow' : '#FADA5E'
//'straw' : '#E4D96F'
//'sugar plum' : '#914E75'
//'sunglow' : '#FFCC33'
//'sunray' : '#E3AB57'
//'sunset' : '#FAD6A5'
//'super pink' : '#CF6BA9'
//'sweet brown' : '#A83731'
//'tan' : '#D2B48C'
//'tangerine' : '#F28500'
//'tango pink' : '#E4717A'
//'tart orange' : '#FB4D46'
//'taupe' : '#483C32'
//'taupe gray' : '#8B8589'
//'tea green' : '#D0F0C0'
//'tea rose' : '#F4C2C2'
//'teal' : '#008080'
//'teal blue' : '#367588'
//'telemagenta' : '#CF3476'
//'tenné' : '#CD5700'
//'terra cotta' : '#E2725B'
//'thistle' : '#D8BFD8'
//'thulian pink' : '#DE6FA1'
//'tickle me pink' : '#FC89AC'
//'tiffany blue' : '#0ABAB5'
//'timberwolf' : '#DBD7D2'
//'titanium yellow' : '#EEE600'
//'tomato' : '#FF6347'
//'tropical rain forest' : '#00755E'
//'true blue' : '#2D68C4'
//'tufts blue' : '#3E8EDE'
//'tumbleweed' : '#DEAA88'
//'turquoise' : '#40E0D0'
//'turquoise blue' : '#00FFEF'
//'turquoise green' : '#A0D6B4'
//'turtle green' : '#8A9A5B'
//'tuscan' : '#FAD6A5'
//'tuscan brown' : '#6F4E37'
//'tuscan red' : '#7C4848'
//'tuscan tan' : '#A67B5B'
//'tuscany' : '#C09999'
//'twilight lavender' : '#8A496B'
//'tyrian purple' : '#66023C'
//'ua blue' : '#0033AA'
//'ua red' : '#D9004C'
//'ultramarine' : '#3F00FF'
//'ultramarine blue' : '#4166F5'
//'ultra pink' : '#FF6FFF'
//'ultra red' : '#FC6C85'
//'umber' : '#635147'
//'unbleached silk' : '#FFDDCA'
//'united nations blue' : '#5B92E5'
//'unmellow yellow' : '#FFFF66'
//'up forest green' : '#014421'
//'up maroon' : '#7B1113'
//'upsdell red' : '#AE2029'
//'usafa blue' : '#004F98'
//'van dyke brown' : '#664228'
//'vanilla' : '#F3E5AB'
//'vanilla ice' : '#F38FA9'
//'vegas gold' : '#C5B358'
//'venetian red' : '#C80815'
//'verdigris' : '#43B3AE'
//'vermilion' : '#D9381E'
//'veronica' : '#A020F0'
//'violet' : '#8F00FF'
//'violet-blue' : '#324AB2'
//'violet-red' : '#891446'
//'viridian' : '#40826D'
//'viridian green' : '#009698'
//'vivid burgundy' : '#9F1D35'
//'vivid sky blue' : '#00CCFF'
//'vivid tangerine' : '#FFA089'
//'vivid violet' : '#9F00FF'
//'volt' : '#CEFF00'
//'warm black' : '#004242'
//'wheat' : '#F5DEB3'
//'white' : '#FFFFFF'
//'wild blue yonder' : '#A2ADD0'
//'wild orchid' : '#D470A2'
//'wild strawberry' : '#FF43A4'
//'wild watermelon' : '#FC6C85'
//'windsor tan' : '#A75502'
//'wine' : '#722F37'
//'wine dregs' : '#673147'
//'winter sky' : '#FF007C'
//'wintergreen dream' : '#56887D'
//'wisteria' : '#C9A0DC'
//'wood brown' : '#C19A6B'
//'yale blue' : '#0F4D92'
//'yellow' : '#FFFF00'
//'yellow-green' : '#9ACD32'
//'yellow orange' : '#FFAE42'
//'yellow sunshine' : '#FFF700'
//'yinmn blue' : '#2E5090'
//'zaffre' : '#0014A8'
//'zomp' : '#39A78E'
//};

QLatin1String Color::componentName(const Component & c) {
    switch(c) {
        case cc_alpha: return QLatin1String("A");
        case cc_rgb_r: return QLatin1String("R");
        case cc_rgb_g: return QLatin1String("G");
        case cc_rgb_b: return QLatin1String("B");
        case cc_hsv_h: return QLatin1String("H");
        case cc_hsv_s: return QLatin1String("S");
        case cc_hsv_v: return QLatin1String("V");
        case cc_hsl_h: return QLatin1String("H");
        case cc_hsl_s: return QLatin1String("S");
        case cc_hsl_l: return QLatin1String("L");
        case cc_hwb_h: return QLatin1String("H");
        case cc_hwb_w: return QLatin1String("W");
        case cc_hwb_b: return QLatin1String("B");
        case cc_cmyk_c: return QLatin1String("C");
        case cc_cmyk_m: return QLatin1String("M");
        case cc_cmyk_y: return QLatin1String("Y");
        case cc_cmyk_k: return QLatin1String("K");

        default: return QLatin1String("Unknown");
    }
}

qreal Color::componentMax(const Component & c, const Metric & metric) {
    if (metric == cm_ranged) {
        switch(c)  {
            case cc_hsv_h:
            case cc_hsl_h:
            case cc_hwb_h: return 359;

            default: return 255;
        }
    }
    else if (metric == cm_percentage)
        return 100.0;
    else return 1.0;
}

void Color::getRgb(qreal & r, qreal & g, qreal & b, qreal & a, const Metric & metric) const {
    switch(metric) {
        case cm_percentage: {
            QColor::getRgbF(&(float&)r, &(float&)g, &(float&)b, &(float&)a);
            r *= 100.0; g *= 100.0; b *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {
            QColor::getRgbF(&(float&)r, &(float&)g, &(float&)b, &(float&)a);
        break;}

        case cm_ranged: {
            int rr, gg, bb, aa;

            QColor::getRgb(&rr, &gg, &bb, &aa);
            r = rr; g = gg; b = bb; a = aa;
        break;}

        default: {
            r = 0; g = 0; b = 0; a = 0;
        }
    }
}
void Color::getHsv(qreal & h, qreal & s, qreal & v, qreal & a, const Metric & metric) const {
    switch(metric) {
        case cm_percentage: {
            QColor::getHsvF(&(float&)h, &(float&)s, &(float&)v, &(float&)a);
            h *= 100.0; s *= 100.0; v *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {
            QColor::getHsvF(&(float&)h, &(float&)s, &(float&)v, &(float&)a);
        break;}

        case cm_ranged: {
            int hh, ss, vv, aa;

            QColor::getHsv(&hh, &ss, &vv, &aa);
            h = hh; s = ss; v = vv; a = aa;
        break;}

        default: {
            h = 0; s = 0; v = 0; a = 0;
        }
    }
}
void Color::getCmyk(qreal & c, qreal & m, qreal & y, qreal & k, qreal & a, const Metric & metric) const {
    QColor col = *this;

    switch(metric) {
        case cm_percentage: {
            col.getCmykF(&(float&)c, &(float&)m, &(float&)y, &(float&)k, &(float&)a);
            c *= 100.0; m *= 100.0; y *= 100.0; k *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {
            col.getCmykF(&(float&)c, &(float&)m, &(float&)y, &(float&)k, &(float&)a);
        break;}

        case cm_ranged: {
            int cc, mm, yy, kk, aa;

            col.getCmyk(&cc, &mm, &yy, &kk, &aa);

            c = cc; m = mm; y = yy; k = kk; a = aa;
        break;}

        default: {
            c = 0; m = 0; y = 0; k = 0; a = 0;
        }
    }
}
void Color::getHsl(qreal & h, qreal & s, qreal & l, qreal & a, const Metric & metric) const {
    switch(metric) {
        case cm_percentage: {
            QColor::getHslF(&(float&)h, &(float&)s, &(float&)l, &(float&)a);
            h *= 100.0; s *= 100.0; l *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {
            QColor::getHslF(&(float&)h, &(float&)s, &(float&)l, &(float&)a);
        break;}

        case cm_ranged: {
            int hh, ss, ll, aa;

            QColor::getHsl(&hh, &ss, &ll, &aa);
            h = hh; s = ss; l = ll; a = aa;
        break;}

        default: {
            h = 0; s = 0; l = 0; a = 0;
        }
    }
}
void Color::getHwb(qreal & h, qreal & w, qreal & b, qreal & a, const Metric & metric) const {
    qreal s, v;

    QColor::getHsvF(&(float&)h, &(float&)s, &(float&)v, &(float&)a);

    hsvToHwb(s, v, w, b);

    switch(metric) {
        case cm_percentage: {
            h *= 100.0; w *= 100.0; b *= 100.0; a *= 100.0;
        break;}

        case cm_proportional: {

        break;}

        case cm_ranged: {
            h *= componentMax(cc_hwb_h); w *= componentMax(cc_hwb_w); b *= componentMax(cc_hwb_b); a *= componentMax(cc_alpha);
        break;}

        default: {
            h = 0; w = 0; b = 0; a = 0;
        }
    }
}

void Color::setRgb(const qreal & r, const qreal & g, const qreal & b, const qreal & a, const Metric & metric) {
    switch(metric) {
        case cm_percentage: {
            QColor::setRgbF(r / 100.0, g / 100.0, b / 100.0, a / 100.0);
        break;}

        case cm_proportional: {
            QColor::setRgbF(r, g, b, a);
        break;}

        case cm_ranged: {
            QColor::setRgb(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), static_cast<int>(a));
        break;}

        default:;
    }
}
void Color::setHsv(const qreal & h, const qreal & s, const qreal & v, const qreal & a, const Metric & metric) {
    switch(metric) {
        case cm_percentage: {
            QColor::setHsvF(h / 100.0, s / 100.0, v / 100.0, a / 100.0);
        break;}

        case cm_proportional: {
            QColor::setHsvF(h, s, v, a);
        break;}

        case cm_ranged: {
            QColor::setHsv(static_cast<int>(h), static_cast<int>(s), static_cast<int>(v), static_cast<int>(a));
        break;}

        default:;
    }
}
void Color::setCmyk(const qreal & c, const qreal & m, const qreal & y, const qreal & k, const qreal & a, const Metric & metric) {
    switch(metric) {
        case cm_percentage: {
            QColor::setCmykF(c / 100.0, m / 100.0, y / 100.0, k / 100.0, a / 100.0);
        break;}

        case cm_proportional: {
            QColor::setCmykF(c, m, y, k, a);
        break;}

        case cm_ranged: {
            QColor::setCmyk(static_cast<int>(c), static_cast<int>(m), static_cast<int>(y), static_cast<int>(k), static_cast<int>(a));
        break;}

        default:;
    }
}
void Color::setHsl(const qreal & h, const qreal & s, const qreal & l, const qreal & a, const Metric & metric) {
    switch(metric) {
        case cm_percentage: {
            QColor::setHslF(h / 100.0, s / 100.0, l / 100.0, a / 100.0);
        break;}

        case cm_proportional: {
            QColor::setHslF(h, s, l, a);
        break;}

        case cm_ranged: {
            QColor::setHsl(static_cast<int>(h), static_cast<int>(s), static_cast<int>(l), static_cast<int>(a));
        break;}

        default:;
    }
}
void Color::setHwb(const qreal & h, const qreal & w, const qreal & b, const qreal & a, const Metric & metric) {
    qreal hh = h, ww = w, bb = b, aa = a;

    switch(metric) {
        case cm_percentage: {
            hh /= 100.0; ww /= 100.0; bb /= 100.0; aa /= 100.0;
        break;}

        case cm_proportional: { break;}

        case cm_ranged: {
            hh /= componentMax(cc_hwb_h);
            ww /= componentMax(cc_hwb_w);
            bb /= componentMax(cc_hwb_b);
            aa /= componentMax(cc_alpha);
        break;}

        default: { return; }
    }

    qreal s, v;

    hwbToHsv(ww, bb, s, v);

    setHsv(hh, s, v, aa, cm_proportional);
}

void Color::setComponent(const Namespace & color_space, const Component & c, const qreal & val, const Metric & metric) {
    if (c == cc_invalid) return;

    qreal c1, c2, c3, c4, a;

    getComponents(color_space, c1, c2, c3, c4, a, metric);

    switch(c) {
        case cc_alpha: { a = val; break;}
        case cc_rgb_r:
        case cc_hsv_h:
        case cc_hsl_h:
        case cc_hwb_h:
        case cc_cmyk_c: { c1 = val; break; }

        case cc_rgb_g:
        case cc_hsv_s:
        case cc_hsl_s:
        case cc_hwb_w:
        case cc_cmyk_m: { c2 = val; break; }

        case cc_rgb_b:
        case cc_hsv_v:
        case cc_hsl_l:
        case cc_hwb_b:
        case cc_cmyk_y: { c3 = val; break; }

        case cc_cmyk_k: { c4 = val; break; }

        default:;
    }

    setComponents(color_space, c1, c2, c3, c4, a, metric);
}

void Color::setComponents(const Namespace & color_space, qreal & c1, qreal & c2, qreal & c3, qreal & c4, qreal & a, const Metric & metric) {
    switch(color_space) {
        case Rgb:   { setRgb(c1, c2, c3, a, metric); break;}
        case Hsv:   { setHsv(c1, c2, c3, a, metric); break;}
        case Cmyk:  { setCmyk(c1, c2, c3, c4, a, metric); break;}
        case Hsl:   { setHsl(c1, c2, c3, a, metric); break;}
        case Hwb:   { setHwb(c1, c2, c3, a, metric);  break;}

        default: {
            c1 = 0; c2 = 0; c3 = 0; c4 = 0; a = 0;
        }
    }
}

void Color::getComponents(const Namespace & color_space, qreal & c1, qreal & c2, qreal & c3, qreal & c4, qreal & a, const Metric & metric) const {
    switch(color_space) {
        case Rgb:   { getRgb(c1, c2, c3, a, metric); c4 = 0; break;}
        case Hsv:   { getHsv(c1, c2, c3, a, metric); c4 = 0; break;}
        case Cmyk:  { getCmyk(c1, c2, c3, c4, a, metric); break;}
        case Hsl:   { getHsl(c1, c2, c3, a, metric); c4 = 0; break;}
        case Hwb:   { getHwb(c1, c2, c3, a, metric); c4 = 0; break;}

        default: {
            c1 = 0; c2 = 0; c3 = 0; c4 = 0; a = 0;
        }
    }
}

Color Color::convertTo(const Namespace & color_space) const Q_DECL_NOTHROW {
    switch(color_space) {
        case Hwb: { return QColor::convertTo(QColor::Hsv); }

        default: {
            QColor::Spec spec = static_cast<QColor::Spec>(color_space);
            return QColor::convertTo(spec);
        }
    }
}

QColor::Spec Color::componentToSpec(const Component & component) {
    switch(component) {
        case cc_alpha: return QColor::Rgb;
        case cc_rgb_r: return QColor::Rgb;
        case cc_rgb_g: return QColor::Rgb;
        case cc_rgb_b: return QColor::Rgb;
        case cc_hsv_h: return QColor::Hsv;
        case cc_hsv_s: return QColor::Hsv;
        case cc_hsv_v: return QColor::Hsv;
        case cc_hsl_h: return QColor::Hsl;
        case cc_hsl_s: return QColor::Hsl;
        case cc_hsl_l: return QColor::Hsl;
        case cc_hwb_h: return QColor::Hsv;
        case cc_hwb_w: return QColor::Hsv;
        case cc_hwb_b: return QColor::Hsv;
        case cc_cmyk_c: return QColor::Cmyk;
        case cc_cmyk_m: return QColor::Cmyk;
        case cc_cmyk_y: return QColor::Cmyk;
        case cc_cmyk_k: return QColor::Cmyk;

        default: return QColor::Invalid;
    };
}
