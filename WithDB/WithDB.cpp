// WithDB.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

const char * path = "C:\\Users\\wxy\\test.db";
std::random_device rd;
std::mt19937 random_engine(rd());

void init();
void testEndian();
void testCache();
void testPage();
void testRelation();
void testDriveBuffer();
void testDrive();
void testTranslator();
void testKeeper();


db::address testsavestr(db::Keeper* k) {
	
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	string teststr[334] = { "bbcs","clear","sides","deal","view","delivered","worse","reporters","have","into",
		"border","time","joint","the","thing","brexiteers","policy","might","prominent","proposals","there","regaining",
		"however","that","street","able","britains","end","negotiate","period","deals","result","another","house:","working",
		"sold","editor","customs","tory","donald","allow","kick","labour","event","export","suggesting","given","uk-eu","us",
		"prevent","exactly","no-one","some","prepare","it","uk","on","laying","advantageous","further","from","moment","mark",
		"currently","people","designed","united","largest","brexit","trump","wants","new","same","kingdom","vote","claiming",
		"mps","economy","great","days","jon","billions","withdrawal","sounds","you","seriously","snps","at","been","around",
		"british","legal","line","has","president","concerned","was","mp","get","washington","because","take","both","market",
		"acknowledged","dups","these","posts","its","aspect","now","delayed","sir","look","independent","suggested","did",
		"referendum","wouldnt","lucas","caroline","an","july","dodds","responding","december","countries","be","good",
		"eurosceptics","which","application","insurance","certainty","five","insisted","after","buts","open","later",
		"bilateral","north","needed","or","green","mays","struck","like","term","free-trade","party","theresa","brought",
		"told","not","until","pm","triggered","insisting","eu","if","again","home","tied","he","specify","dont","more",
		"through","basis","francois","trumps","sign","we","host","far","fought","had","members","may","appear","agreed",
		"2021","trade","including","before","pounds","absolutely","return","dem","being","businesses","as","hours","iain",
		"knew","visit","will","carry","between","vince","whether","single","parliament","fear","transition","fishermen",
		"could","over","unveiled","post-brexit","botched","force","of","way","2020","least","blackford","backstop","scottish",
		"meant","states","spokesman","while","leader","said","aims","prime","commons","were","provocative","unable","all","leave",
		"determine","bad","control","jeremy","for","to","with","doing","urge","met","senior","groups","her","forging","written",
		"times","lib","added","sopel","remarks","dodo","mrs","cable","strike","mr","put","downing","faced","allowed","criticism",
		"heavy","us-uk","rules","by","sunday","irish","much","administration","laws","money","full","very","world","can","america",
		"communication","in","nigel","his","under","flows","ifs","but","right","this","11","dead","threaten","sustained","others",
		"come","our","they","agreement","no","and","think","him","came","comments","what","white","called","january","formed","out",
		"is","long","outside","use","already","10","britain","so","groundwork","monday","during","possible","off","among","continue",
		"backbencher","she","corbyn","borders","ambitious","brussels","would","minister","absolute" };
	vector<string> data;
	for (int i = 0;i < 334;i++) {
		data.push_back(teststr[i]);
	}
	shuffle(data.begin(), data.end(), default_random_engine(static_cast<unsigned int>(seed)));

	db::IndexGuard<string> igg(k);
	db::address res = igg.iroot;

	cout << "root节点地址是" << igg.iroot << endl;
	int v = 1;
	for (vector<string>::iterator it = data.begin();it != data.end();++it) {
		igg.allocate(*it, v);
		v++;
	}
	igg.print(15);
	return res;
}

void testloadstr(db::Keeper* k,db::address res) {
	db::IndexGuard<string> igg(k,res);
	igg.print(15);
}

void testdelstr(db::Keeper* k,db::address res) {
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	string teststr[334] = { "bbcs","clear","sides","deal","view","delivered","worse","reporters","have","into",
		"border","time","joint","the","thing","brexiteers","policy","might","prominent","proposals","there","regaining",
		"however","that","street","able","britains","end","negotiate","period","deals","result","another","house:","working",
		"sold","editor","customs","tory","donald","allow","kick","labour","event","export","suggesting","given","uk-eu","us",
		"prevent","exactly","no-one","some","prepare","it","uk","on","laying","advantageous","further","from","moment","mark",
		"currently","people","designed","united","largest","brexit","trump","wants","new","same","kingdom","vote","claiming",
		"mps","economy","great","days","jon","billions","withdrawal","sounds","you","seriously","snps","at","been","around",
		"british","legal","line","has","president","concerned","was","mp","get","washington","because","take","both","market",
		"acknowledged","dups","these","posts","its","aspect","now","delayed","sir","look","independent","suggested","did",
		"referendum","wouldnt","lucas","caroline","an","july","dodds","responding","december","countries","be","good",
		"eurosceptics","which","application","insurance","certainty","five","insisted","after","buts","open","later",
		"bilateral","north","needed","or","green","mays","struck","like","term","free-trade","party","theresa","brought",
		"told","not","until","pm","triggered","insisting","eu","if","again","home","tied","he","specify","dont","more",
		"through","basis","francois","trumps","sign","we","host","far","fought","had","members","may","appear","agreed",
		"2021","trade","including","before","pounds","absolutely","return","dem","being","businesses","as","hours","iain",
		"knew","visit","will","carry","between","vince","whether","single","parliament","fear","transition","fishermen",
		"could","over","unveiled","post-brexit","botched","force","of","way","2020","least","blackford","backstop","scottish",
		"meant","states","spokesman","while","leader","said","aims","prime","commons","were","provocative","unable","all","leave",
		"determine","bad","control","jeremy","for","to","with","doing","urge","met","senior","groups","her","forging","written",
		"times","lib","added","sopel","remarks","dodo","mrs","cable","strike","mr","put","downing","faced","allowed","criticism",
		"heavy","us-uk","rules","by","sunday","irish","much","administration","laws","money","full","very","world","can","america",
		"communication","in","nigel","his","under","flows","ifs","but","right","this","11","dead","threaten","sustained","others",
		"come","our","they","agreement","no","and","think","him","came","comments","what","white","called","january","formed","out",
		"is","long","outside","use","already","10","britain","so","groundwork","monday","during","possible","off","among","continue",
		"backbencher","she","corbyn","borders","ambitious","brussels","would","minister","absolute" };
	vector<string> data;
	for (int i = 0;i < 334;i++) {
		data.push_back(teststr[i]);
	}
	shuffle(data.begin(), data.end(), default_random_engine(static_cast<unsigned int>(seed)));
	
	db::IndexGuard<string> igg(k, res);
	//db::bptree<std::string>* tr = new db::bptree<std::string>(k, res);
	int v = 1;
	for (vector<string>::iterator it = data.begin();it != data.end();++it) {
		igg.free(*it);
		//tr->delkey(*it);
		v++;
		if (v > 300) {
			break;
			
			//tr->print_tree(15);
		}
	}
	igg.print(15);
	//tr->close();
}

db::address testsaveint(db::Keeper* k) {
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	vector<int> arr;
	for (int i = 1;i < 500;i++) {
		arr.push_back(i);
	}
	shuffle(arr.begin(), arr.end(), default_random_engine(static_cast<unsigned int>(seed)));
	//random_shuffle(arr.begin(), arr.end());
	db::bptree<int>* tr = new db::bptree<int>(k);
	cout << "root节点地址是" << tr->pointroot << endl;
	db::address res = tr->pointroot;
	int v = 1;
	for (vector<int>::iterator it = arr.begin();it != arr.end();++it) {
		tr->insert(*it, v);
		//tr->print_tree(3);
		v++;
	}
	tr->print_tree(3);
	//tr->print_leaf();
	tr->close();
	return res;
}

void testloadint(db::Keeper* k,db::address res) {
	db::bptree<int>* tr = new db::bptree<int>(k, res);
	tr->print_tree(3);
	//tr->print_leaf();
	tr->close();
}

void testdelint(db::Keeper* k,db::address res) {
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	vector<int> arr;
	for (int i = 1;i < 250;i++) {
		arr.push_back(i);
	}
	db::bptree<int>* tr = new db::bptree<int>(k, res);
	shuffle(arr.begin(), arr.end(), default_random_engine(static_cast<unsigned int>(seed)));
	int v = 1;
	for (vector<int>::iterator it = arr.begin();it != arr.end();++it) {
		tr->delkey(*it);
		v++;
		//if(v%100==0){
		//if (v > 470 || v % 100 == 0) {
			//tr->print_tree(3);
		//}
		//tr->print_tree(3);
	}
	tr->print_tree(3);
	tr->close();
}

int main()
{
	// init();
	// testEndian();
	// testCache();
	// testPage();
	// testRelation();
	// testDriveBuffer();
	// testDrive();
	// testTranslator();
	// testKeeper();
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	// test6();
	// test7();
	
	
	db::Keeper keeper(path, false);
	keeper.start();

	db::address r1, r2, r3, r4;
	r4 = testsaveint(&keeper);
	r1 = testsavestr(&keeper);

	testloadstr(&keeper, r1);
	testloadint(&keeper, r4);
	testdelint(&keeper, r4);
	testdelstr(&keeper, r1);

	r2 = testsavestr(&keeper);
	r3 = testsaveint(&keeper);
	testloadint(&keeper, r3);
	testloadstr(&keeper, r2);
	testdelstr(&keeper, r2);
	testdelint(&keeper, r3);

	keeper.stop();
	keeper.close();
	return 0;
}


#include <unordered_set>

void init() {
	cout << hex;
	ios::sync_with_stdio(false);
}

void testEndian() {
	for (double i = 0.01234; i < 0.01234  + 0.7; i += 0.1) {
		cout << db::decode<double>(db::encode(i)) << endl;
	}
}

db::size_t testHash(int addr) {
	return static_cast<db::size_t>(addr);
}

void testCache() {
	struct TestHandler : db::BasicCacheHandler<int, string> {
		bool onInsert(int addr, string &value) {
			value = to_string(addr + 1);
			return true;
		}

		bool onHit(int addr, string &value) {
			cout << "hit " << addr << endl;
			return true;
		}

		bool onErase(int addr, string &value) {
			cout << "kick " << addr << endl;
			return true;
		}
	};
	{
		
		TestHandler h;
		db::Cache<int, string, TestHandler, db::HashCacheCore<int, testHash>> c(h, 4);
		for (auto i = 8; i < 16; ++i) {
			cout << c.fetch(i) << endl;
		}
		for (auto i = 0; i < 4; ++i) {
			cout << c.fetch(i) << endl;
		}
		try {
			cout << c.fetch(4) << endl;
		} catch (std::runtime_error e) {
			cout << e.what() << endl;
		}
		for (auto i = 0; i < 8; ++i) {
			cout << c.fetch(i) << endl;
		}
		try {
			c.close();
		} catch (std::runtime_error e) {
			cout << e.what() << endl;
		}
	}
	{
		TestHandler h;
		db::Cache<int, string, TestHandler> c(h, 4);
		for (auto i = 8; i < 16; ++i) {
			cout << c.fetch(i) << endl;
		}
		for (auto i = 0; i < 4; ++i) {
			cout << c.fetch(i) << endl;
			c.pin(i);
		}
		try {
			cout << c.fetch(4) << endl;
		} catch (std::runtime_error e) {
			cout << e.what() << endl;
		}
		c.unpin(0);
		for (auto i = 0; i < 8; ++i) {
			cout << c.fetch(i) << endl;
		}
		try {
			c.close();
		} catch (std::runtime_error e) {
			cout << e.what() << endl;
		}
		for (auto i = 0; i < 8; ++i) {
			c.unpin(i);
		}
	}
}

void testPage() {
	{
		db::Container c;
		db::Page p(c, 0);
		for (int i = 0; i < 100; i += 4) {
			p.write(i, i);
		}
		for (int i = 0; i < 100; i += 4) {
			cout << p.read<int>(i) << endl;
		}
		string x = "123456789123456789123456789";
		p.write(x, 0);
		cout << p.read<string>(0) << endl;
	}
	struct TestHandler : db::BasicCacheHandler<int, db::Page> {
		bool onInsert(int addr, db::Page &p) {
			p.write(addr, 0);
			p.write("content = " + std::to_string(addr + 1), 4);
			return true;
		}
		bool onHit(int addr, db::Page &p) {
			cout << "hit " << addr << ' ' << p.read<string>(4) << endl;
			return true;
		}

		bool onErase(int addr, db::Page &p) {
			cout << "kick " << addr  << ' '<< p.read<string>(4) << endl;
			return true;
		}
	};
	{
		TestHandler h;
		db::Cache<int, db::Page, TestHandler> c(h, 4);
		for (auto i = 8; i < 16; ++i) {
			cout << c.fetch<db::Page>(i)->read<int>(0) << endl;
		}
		for (auto i = 0; i < 4; ++i) {
			cout << c.fetch<db::Page>(i)->read<int>(0) << endl;
			c.pin(i);
		}
		try {
			cout << c.fetch<db::Page>(5)->read<int>(0) << endl;
		} catch (std::runtime_error e) {
			cout << e.what() << endl;
		}
		c.unpin(0);
		for (auto i = 0; i < 8; ++i) {
			cout << c.fetch<db::Page>(i)->read<int>(0) << endl;
		}
		try {
			c.close();
		} catch (std::runtime_error e) {
			cout << e.what() << endl;
		}
		for (auto i = 0; i < 8; ++i) {
			c.unpin(i);
		}
	}
}

void testRelation() {
	db::Relation table;
	auto f = table.add(db::AttributeEntry("1", db::INT_T))
		.add(db::AttributeEntry("2", db::CHAR_T, 18))
		.add(db::AttributeEntry("3", db::VARCHAR_T, 100))
		.add(db::AttributeEntry("4", db::INT_T))
		.add(db::AttributeEntry("5", db::CHAR_T, 15))
		.add(db::AttributeEntry("6", db::DOUBLE_T))
		.add(db::AttributeEntry("7", db::VARCHAR_T, 50))
		.format();
	auto builder = table.builder();
	for (auto i = 0; i < 0x1; ++i) {
		db::TupleContainer c(table.maxTupleSize());
		auto tmp = builder.start(c)
			.build(1, 0)
			.build(string("Supplier#000000001"), 1)
			.build(string("N kD4on9OM Ipw3, gf0JBoQDd7tgrzrddZ"), 2)
			.build(17, 3)
			.build(string("27-918-335-1736"), 4)
			.build(5755.94, 5)
			.build(string("each slyly above the careful"), 6)
			.result();
		cout << table.read<int>(tmp, 0) << endl;
		cout << table.read<string>(tmp, 1) << endl;
		cout << table.read<string>(tmp, 2) << endl;
		cout << table.read<int>(tmp, 3) << endl;
		cout << table.read<string>(tmp, 4) << endl;
		cout << table.read<double>(tmp, 5) << endl;
		cout << table.read<string>(tmp, 6) << endl;
	}
}

// for temporary use to save strange file
void testDriveBuffer() {
	db::Container c(db::PAGE_SIZE);
	db::Page p(c, 0);
	{
		db::DriveBuffer buf(path, true);
		cout << buf.isOpen() << endl;
		cout << buf.size() << endl;
		buf.expand(db::PAGE_SIZE * 10);
		for (auto i = 0; i < 10; ++i) {
			p.write(0.123456 + 0.1 * i, 0);
			buf.put(p, i * db::PAGE_SIZE);
		}
		for (auto i = 9; i >= 0; --i) {
			buf.get(p, i * db::PAGE_SIZE);
			cout << p.read<double>(0) << endl;
		}
	}
	{
		db::DriveBuffer buf(path);
		cout << buf.size() << endl;
		for (auto i = 9; i >= 0; --i) {
			buf.get(p, i * db::PAGE_SIZE);
			cout << p.read<double>(0) << endl;
		}
	}
}

void testDrive() {
	unordered_set<db::drive_address> addrs;
	{
		db::Drive ctrl(path, true);
		for (int i = 0x1000; i > 0; --i) {
			auto ret = ctrl.allocate(i * db::PAGE_SIZE);
			// cout << ret << endl;
			if (ret % db::PAGE_SIZE) {
				cout << ret << endl;
			}
			if (addrs.find(ret) != addrs.end()) {
				throw runtime_error("testDrive");
			}
			addrs.insert(ret);
		}
		cout << addrs.size() << endl;
		for (auto addr : addrs) {
			ctrl.free(addr);
		}
		unordered_set<db::drive_address> s;
		auto t = ctrl._entry._userMasters.back();
		size_t cnt = 0;
		while (t) {
			if (s.find(t) != s.end()) {
				throw runtime_error("testDrive");
			}
			s.insert(t);
			auto ptr = ctrl._user._cache.fetch<db::DriveMasterPage>(t);
			if (t <= ptr->_forward) {
				throw runtime_error("testDrive");
			}
			t = ptr->_forward;
			cnt += ptr->_slaves.size();
		}
		cout << s.size() + cnt << endl;
		addrs.clear();
		for (int i = 0x100; i > 0; --i) {
			auto ret = ctrl.allocate(i * db::PAGE_SIZE);
			if (ret % db::PAGE_SIZE) {
				cout << ret << endl;
			}
			if (addrs.find(ret) != addrs.end()) {
				throw runtime_error("testDrive");
			}
			addrs.insert(ret);
		}
	}
	{
		db::Drive ctrl(path, false);
		for (auto addr : addrs) {
			ctrl.free(addr);
		}
		unordered_set<db::drive_address> s;
		auto t = ctrl._entry._userMasters.back();
		size_t cnt = 0;
		while (t) {
			if (s.find(t) != s.end()) {
				throw runtime_error("testDrive");
			}
			s.insert(t);
			auto ptr = ctrl._user._cache.fetch<db::DriveMasterPage>(t);
			if (t <= ptr->_forward) {
				throw runtime_error("testDrive");
			}
			t = ptr->_forward;
			cnt += ptr->_slaves.size();
		}
	}
	
}

void testTranslator() {
	size_t data_segment = db::Translator::segmentBegin(db::DATA_SEG) * db::SEGMENT_SIZE;
	unordered_map<db::address, db::drive_address> record;

	{
		db::Drive drive(path, true);
		db::Translator translator(drive);
		translator._params[0].first = 1;
		for (int i = 0; i < 0x100; ++i) {
			auto x = data_segment + i * db::PAGE_SIZE;
			auto y = drive.allocate();
			translator.link(x, y);
			record[x] = y;
		}
		for (int i = 0; i < 0x1000; ++i) {
			std::uniform_int_distribution<> dis(0, 0xff);
			auto x = data_segment + dis(random_engine) * db::PAGE_SIZE;
			if (record[x] != translator(x)) {
				throw runtime_error("testTranslator");
			}
		}
		for (int i = 0; i < 0x100; ++i) {
			auto x = data_segment + i * db::PAGE_SIZE;
			translator.unlink(x);
		}
		for (int i = 0; i < 0x100; ++i) {
			auto x = data_segment + i * db::PAGE_SIZE;
			bool flag;
			translator(x, flag);
			if (flag) {
				throw runtime_error("testTranslator");
			}
		} // TODO: relink
		for (int i = 0; i < 0x1000; ++i) {
			auto x = data_segment + i * db::PAGE_SIZE;
			auto y = drive.allocate();
			translator.link(x, y);
			record[x] = y;
		}
	}
	{
		db::Drive drive(path, false);
		db::Translator translator(drive);
		auto t = db::current();
		for (int i = 0; i < 0x100; ++i) {
			for (int j = 0; j < 0x1000; ++j) {
				auto x = data_segment + j * db::PAGE_SIZE;
				if (record[x] != translator(x)) {
					throw runtime_error("testTranslator");
				}
			}
		}
		cout << db::current() - t << endl;
	}
}

void testKeeper() {
	size_t data_segment = db::Translator::segmentBegin(db::DATA_SEG) * db::SEGMENT_SIZE;

	{
		db::Keeper keeper(path, true);
		keeper.start();
		keeper._translator._params[0].first = 1;
		for (int i = 0; i < 0x100; ++i) {
			auto x = data_segment + i * db::PAGE_SIZE;
			auto y = keeper.hold<db::VirtualPage>(x);
			y->write(-i, 0);
		}
		for (int i = 0; i < 0x1000; ++i) {
			std::uniform_int_distribution<> dis(0, 0xff);
			int j = dis(random_engine);
			auto x = data_segment + j * db::PAGE_SIZE;
			auto y = keeper.hold<db::VirtualPage>(x)->read<int>(0);
			if (y != -j) {
				throw runtime_error("testKeeper");
			}
		}
		for (int i = 0; i < 0x100; ++i) {
			auto x = data_segment + i * db::PAGE_SIZE;
			keeper.loosen(x);
		}
		for (int i = 0; i < 0x100; ++i) {
			auto x = data_segment + i * db::PAGE_SIZE;
			if (keeper.hold<db::VirtualPage>(x)->read<int>(0) != 0) {
				throw runtime_error("testKeeper");
			}
		} // TODO: relink
		for (int i = 0; i < 0x1000; ++i) {
			auto x = data_segment + i * db::PAGE_SIZE;
			auto y = keeper.hold<db::VirtualPage>(x);
			y->write(-i, 0);
		}
	}
	{
		db::Keeper keeper(path, false);
		keeper.start();
		auto t = db::current();
		for (int i = 0; i < 0x100; ++i) {
			for (int j = 0; j < 0x1000; ++j) {
				auto x = data_segment + j * db::PAGE_SIZE;
				if (keeper.hold<db::VirtualPage>(x)->read<int>(0) != -j) {
					throw runtime_error("testKeeper");
				}
			}
		}
		cout << db::current() - t << endl;
	}
}
