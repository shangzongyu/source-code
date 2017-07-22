#include "NewsDialog.h"

typedef struct {
	char * news_title, * image_filename;
	char * news_in_Chinese,  * news_in_English;
} News_Info;
		
News_Info news_2011[10] = {
	{"日本海啸", "images/Japan_Tsunami.jpg",
	"3月14日，日本岩手县大槌町，一艘船被冲到屋顶，四周被无数碎片包围。\n"
	"11日，日本东北部海域发生8.9级地震并引发可怕的海啸。日本地震和海啸\n"
	"导致福岛第一核电站发生泄漏事故，放射性物质泄漏到周边地区。这是自\n"
	"1986年切尔诺贝利核事故之后世界上最严重的核灾难。",
	"A tsunami-tossed boat rests on top of a building amid a sea of debris in Otsuchi, Iwate Prefecture, on March 14 --days after a magnitude 8.9 earthquake struck off the northeastern coast of Japan, triggering adevastating tsunami.The Japan earthquake and tsunami also led to a crisis at the Fukushima Daiichi nuclear power plant, which leaked radioactive material into the surrounding region. The accident is now regarded as the largest nuclear disaster since the Chernobyl incident in 1986."},

	{"51号区间谍飞机","images/spy_plane.jpg",
	"上世纪50年代晚期，神秘的美国51号区，一架钛材料A-12间谍飞机原型机\n"
	"准备接受雷达测试。经过一系列解密之后，内华达基地51号区在冷战期间\n"
	"的诸多细节最终大白于天下，其中包括5月公布的A-12侦察机坠机以及有关\n"
	"掩盖坠机事故真相的照片。这些照片此前从未对外公开过。雷达几乎无法\n"
	"探测到A-12，其时速可达到2200英里(每小时3540公里)，足以在70分钟内\n"
	"横跨美国大陆。这种间谍飞机能够在9万英尺(2.74万米)的高度拍摄到地面\n"
	"上只有1英尺(30厘米)长的物体。但提升性能极限也不可避免地带来风险，\n"
	"1963年，一架A-12间谍飞机在51号区附近坠毁。",
	"Suspended upside down, a titanium A-12 spy-plane prototype is prepped for radar testing at Area 51 in the late 1950s.After a rash of declassifications, details of Cold War workings at the Nevada base, which to this day does not officially exist, are coming to light--including images of an A-12 crash and its cover-up pictured publicly for the first time in May.Nearly undetectable to radar, the A-12 could fly at 2,200 miles (3,540 kilometers) an hour--fast enough to cross the continental U.S. in 70 minutes. From 90,000 feet (27,400 meters),the plane's cameras could capture foot-long (0.3-meter-long) objects on the ground below. But pushing the limits came with risks--and led to the catastrophic 1963 crash of an A-12 based out of Area 51."},

	{"墨西哥海底雕塑","images/underwater_bodies.jpg",
	"2011年1月，在墨西哥坎昆附近拍摄的这张照片展现了一名潜泳者从真人大小\n"
	"的雕塑上方游过的景象。这些真人大小的雕塑出自英国雕塑家\n"
	"詹森·德卡莱斯·泰勒之手，被安放在加勒比海海底，占地面积\n"
	"超过4520平方英尺(约合420平方米)。博物馆在一份声明中表示：\n"
	"“这是世界上规模最大同时最壮观的水下景观之一。”由于海洋\n"
	"污染，海水温度上升以及过度捕捞，墨西哥的珊瑚礁面临威胁。\n"
	"泰勒希望水下雕塑能够转移游客的视线，让他们将兴趣从珊瑚礁\n"
	"移到这些雕塑身上。据统计，每年有近75万游客游览当地的珊瑚礁。",
	"A snorkeler swims over life-size statues near Cancún, Mexico, in a picture released in January.Created by Mexico-based British sculptor Jason deCaires Taylor, the Caribbean installation is intended to eventually cover more than 4,520 square feet (420 square meters),which would make it \"one of the largest and most ambitious underwater attractions in the world,\" according to a museum statement. In doing so, Taylor hopes Mexico's natural reefs, which are already stressed by marine pollution, warming waters, and overfishing, can catch a break from the approximately 750,000 tourists who visit the area each year."},

	{"独眼鲨鱼","images/Shark.jpg",
	"10月在墨西哥发现的罕见独眼鲨鱼胎儿。这个胎儿身长22英寸(56厘米)，\n"
	"只有一只眼睛，长在头部前部。它患有一种名为“独眼畸形”的先天性疾病，\n"
	"很多动物都会出现独眼畸形，包括人类在内。杰克逊维尔北佛罗里达州大学\n"
	"研究鲨鱼的生物学家吉姆·格尔雷切特表示，科学家此前就曾多次发现\n"
	"独眼鲨鱼胎儿。但他们一直未能在母体外捕获独眼鲨鱼，说明这种鲨鱼\n"
	"无法在野外存活很久。",
	"This extremely rare cyclops shark, found in Mexico, was confirmed by scientists in October. The 22-inch-long (56-centimeter-long) fetus has a single, functioning eye at the front of its head. The eye is a hallmark of a congenital condition called cyclopia, which occurs in several animal species, including humans.　Scientists have documented cyclops-shark embryos a few times before, said Jim Gelsleichter, a shark biologist at the University of North Florida in Jacksonville. The fact that none have been caught outside the wombsuggests cyclops sharks don't survive long in the wild."},

	{"日本火灾洪水","images/Japan_fire_flood.jpg",	
	"3月11日，日本遭受8.9级大地震袭击并引发可怕海啸。灾难发生后，\n"
	"无数房屋被泡在洪水中，部分起火燃烧。当地时间下午2点46分，\n"
	"大地震袭击仙台沿海81英里(130公里)的海域。地震引发的海啸随即\n"
	"袭击这个大约100万人口的港口城市，海浪高度达到33英尺(10米)。\n"
	"这是日本140年来遭受的最大地震，距离震中大约250英里(400公里)\n"
	"的东京也感到震感和余震。",
	"Houses burn amid flood waters on March 11 after a magnitude 8.9 earthquake off the coast of Japan triggered a powerful tsunami。The earthquake--the strongest in Japan in 140 years--struck 81 miles (130 kilometers) off the coast of Sendai at 2:46 p.m. local time. A port city of about a million residents, Sendai was hit by tsunami waves up to 33 feet (10 meters) high.The earthquake and its aftershocks were felt as far away as Tokyo, about 250 miles (400 kilometers) from the epicenter。"},

	{"911十周年纪念","images/911.jpg",
	"在纽约的一条街道，当地居民浏览警察和消防员的照片，2001年9月11日\n"
	"恐怖袭击后，他们就下落不明。纽约国家9·11纪念馆/博物馆负责人、\n"
	"9·11文物照片集《残留的记忆》编辑克利福德·查宁表示：“所有幸存者\n"
	"都对我说，看着消防员脸上的表情，他们就知道情况有多糟，他们可能出\n"
	"不去了。他们清楚地知道自己面临着什么，在危险面前，他们表现出令人\n"
	"敬佩的勇气和英雄品质。”",
	"People on a New York City street scan pictures of the many police and fire personnel still missing in the wake of the September 11, 2001, terrorist attacks.\"I've heard from any number of survivors that they could tell by looking at firefighters' faces [the firefighters] knew how bad this was and that they might not get out,\" said Clifford Chanin, an executive at New York City's National 9/11 Memorial and Museum and editor of Memory Remains, a photographic book of 9/11 artifacts. \"They knew what they were facing, and the heroism and courage [they showed] is just astonishing.\""},

	{"寄生真菌","images/fungus.jpg",
	"巴西雨林，僵尸蚂蚁的头部向外长出一根类似茎干的物体，这根“茎干”\n"
	"实际上是一种新发现的真菌，名为“Ophiocordyceps camponoti-balzani”。\n"
	"科学家3月表示，这种真菌最初被认为是单一物种，名为“Ophiocordyceps \n"
	"unilateralis”，但实际上有4个截然不同的种群，并且全部能够对蚂蚁\n"
	"进行大脑寄生。Ophiocordyceps camponoti-balzani能够感染蚂蚁并占领\n"
	"它们的大脑，一旦蚂蚁移动到最适于它们生长和传播孢子的区域，它们便会\n"
	"痛下杀手，杀死蚂蚁。",
	"A stalk of the new fungus species Ophiocordyceps camponoti-balzani grows out of a \"zombie\" ant's head in a Brazilian rain forest.Originally thought to be a single species, called Ophiocordyceps unilateralis, the fungus is actually four distinct species--all of which can \"mind control\" ants, scientists announced in March.The fungus can infect an ant, take over its brain, and then kill the insect once the it moves to an ideal location for growing and spreading the fungus's spores."},

	{"捕获最大鳄鱼","images/crocodile.jpg",
	"经过长达3周的搜捕，一条长达21英尺(6.4米)的咸水鳄最终在菲律宾“落网”。\n"
	"官员们9月表示这可能是迄今为止捕获的体型最大的鳄鱼。这条鳄鱼重\n"
	"2369磅(1075公斤)，被命名为Lolong，曾多次袭击人类，共造成两人死亡。\n"
	"目前，Lolong临时被“囚禁”在棉兰老岛一个围栏内。",
	"Caught alive after a three-week hunt, an allegedly 21-foot-long (6.4-meter-long) saltwater crocodile caught in the Philippines may be the largest crocodile yet captured, officials said in September.　The 2,369-pound (1,075-kilogram) crocodile is suspected of attacking several people and killing two. The animal, named Lolong, survived capture and was held in a temporary enclosure near Bunawan township (map)."},
			
	{"亚特兰蒂斯号","images/space_shuttle.jpg",	
	"2000年9月8日，“亚特兰蒂斯”号航天飞机从美国佛罗里达州的肯尼迪\n"
	"航天中心发射升空。在附近的可可海滩，海上的冲浪爱好者目睹了\n"
	"“亚特兰蒂斯”号飞向云霄的景象。美国《国家地理杂志》的编辑\n"
	"将这幅照片评为美国宇航局航天飞机计划最令人难忘的照片之一。\n"
	"7月，“亚特兰蒂斯”号完成STS-135任务。这是历时30年的航天飞机\n"
	"计划的最后一次太空任务。STS-135任务指挥官克里斯托弗·弗格森\n"
	"在国际空间站接受采访时说：“航天飞机是近30年的人类太空飞行计划\n"
	"的核心和灵魂，看到它们退役，我难免感到一丝伤感。",
	"Cocoa Beach surfers watch from the water as the space shuttle Atlantis lifts off from nearby Kennedy Space Center in Florida on September 8, 2000.The shot was among those chosen by National Geographic editors as the most unforgettable pictures from the entire NASA shuttle program.In July Atlantis completed STS-135, the final shuttle mission in the program's 30-year history.\" The space shuttle has been with us at the heart and soul of the human spaceflight program for about 30 years, and it's a little sad to see it go away,\" STS-135 mission commander Christopher Ferguson told reporters in a televised interview from the International Space Station."},

	{"巴基斯坦蛛网树","images/web_wrapped_tree.jpg",
	"巴基斯坦信德省的一个村落，一片被洪水淹没的农田边的树上出现\n"
	"壮观的蜘蛛网，好似一个巨大的茧。为了躲避可怕的洪水，数百万只\n"
	"蜘蛛--可能还有其他昆虫--爬到树上结网。2010年7月，巴基斯坦\n"
	"普降大雨，短短一周内的降雨量便几乎等同于与近10年的降雨量，\n"
	"导致很多河流暴涨。随着洪水缓慢退却，巴基斯坦农村地区出现巨大的水坑。",
	"Trees shrouded in ghostly cocoons line the edges of a submerged farm field in the Pakistani village of Sindh, where massive floods drove millions of spiders and possibly other insects into the trees to spin their webs.　Beginning last July, unprecedented monsoons dropped nearly ten years' worth of rainfall on Pakistan in one week, swelling the country's rivers. The water was slow to recede, creating vast pools of stagnant water across the countryside."}
};

NewsDialog::NewsDialog()
{
	listWidget = new QListWidget(this);
	listWidget->setViewMode(QListView::IconMode);
    listWidget->setIconSize(QSize(120, 80));
    listWidget->setMovement(QListView::Static);
	listWidget->setFixedWidth(340);
    listWidget->setSpacing(12);
    
	for ( int i=0; i<10; i++) {
		News_Info news = news_2011 [i];		
		QListWidgetItem * item = new QListWidgetItem(listWidget);
		item->setData(Qt::DisplayRole,		QObject::tr(news.news_title) );
		item->setData(Qt::DecorationRole,	QIcon(news.image_filename) );
		item->setData(Qt::TextAlignmentRole,Qt::AlignHCenter );		
		item->setData(Qt::ToolTipRole,		QString( QObject::tr(news.news_in_Chinese)) );
		item->setData(Qt::UserRole,			QString( news.news_in_English) );
	}
	connect(listWidget,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changeNews(QListWidgetItem *, QListWidgetItem*)));

	image = new QLabel(this);
	news  = new QLabel(this);
	news->setWordWrap( true );
	news->setFont( QFont("Times New Roman",16) );

	QVBoxLayout *right = new QVBoxLayout;
	right->addWidget(image);
	right->addWidget(news);
  
	QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(right);
    setLayout(mainLayout);

    setWindowTitle(tr("2011 Top News"));
}

void NewsDialog::changeNews(QListWidgetItem *current, QListWidgetItem *previous)
{
	int row = listWidget->row( current );
	image->setPixmap( QPixmap( news_2011[row].image_filename ) );
	news->setText( current->data(Qt::UserRole).toString() );
}