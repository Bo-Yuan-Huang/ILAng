#include "systemc.h"
#include <map>
SC_MODULE(TEST) {
  sc_in< sc_biguint<2> > TEST_cmd_in;
  sc_biguint<2> TEST_cmd;
  sc_in< sc_biguint<16> > TEST_cmdaddr_in;
  sc_biguint<16> TEST_cmdaddr;
  sc_in< sc_biguint<8> > TEST_cmddata_in;
  sc_biguint<8> TEST_cmddata;
  sc_in<bool> TEST_cmdflag_in;
  bool TEST_cmdflag;
  sc_out< sc_biguint<2> > TEST_status_out;
  sc_biguint<2> TEST_status;
  sc_out< sc_biguint<16> > TEST_address_out;
  sc_biguint<16> TEST_address;
  sc_out< sc_biguint<16> > TEST_length_out;
  sc_biguint<16> TEST_length;
  sc_out< sc_biguint<128> > TEST_counter_out;
  sc_biguint<128> TEST_counter;
  sc_biguint<8> TEST_XRAM[65536];
  sc_out<bool> TEST_flag_out;
  bool TEST_flag;
  std::map< sc_biguint<32>, sc_biguint<32> > TEST_big_ram;
  sc_biguint<128> ENCRYPT_rd_data;
  sc_biguint<128> ENCRYPT_enc_data;
  sc_biguint<4> ENCRYPT_byte_cnt;
  sc_biguint<16> ENCRYPT_blk_cnt;
  bool decode_97151();
  bool c_97123;
  bool c_97119;
  bool c_97125;
  bool c_97148;
  bool c_97141;
  bool c_97143;
  bool c_97145;
  bool c_97150;
  bool c_97137;
  bool c_97151;
  bool decode_97188();
  bool c_97185;
  bool c_97181;
  bool c_97187;
  bool c_97177;
  bool c_97188;
  bool decode_97224();
  bool c_97202;
  bool c_97204;
  bool c_97224;
  bool decode_97501();
  bool c_97499;
  bool c_97495;
  bool c_97501;
  bool decode_97523();
  bool c_97523;
  sc_biguint<16> decode_97151_update_TEST_address();
  bool c_97128;
  bool c_97163;
  sc_biguint<8> c_97159;
  sc_biguint<8> c_97165;
  bool c_97156;
  sc_biguint<8> c_97152;
  sc_biguint<8> c_97158;
  sc_biguint<16> c_97170;
  sc_biguint<16> c_97172;
  bool decode_97151_update_TEST_flag();
  bool c_97173;
  sc_biguint<2> decode_97188_update_TEST_status();
  sc_biguint<2> unknown0();
  sc_biguint<2> c_97191;
  sc_biguint<2> c_97194;
  sc_biguint<4> decode_97224_update_ENCRYPT_byte_cnt();
  sc_biguint<4> c_97228;
  sc_biguint<128> decode_97224_update_ENCRYPT_rd_data();
  sc_biguint<4> c_97473;
  bool c_97476;
  sc_biguint<16> c_97231;
  sc_biguint<16> c_97229;
  sc_biguint<16> c_97232;
  sc_biguint<8> c_97233;
  sc_biguint<8> c_97469;
  sc_biguint<8> c_97478;
  sc_biguint<4> c_97457;
  bool c_97460;
  sc_biguint<8> c_97453;
  sc_biguint<8> c_97462;
  sc_biguint<4> c_97441;
  bool c_97444;
  sc_biguint<8> c_97437;
  sc_biguint<8> c_97446;
  sc_biguint<4> c_97425;
  bool c_97428;
  sc_biguint<8> c_97421;
  sc_biguint<8> c_97430;
  sc_biguint<4> c_97409;
  bool c_97412;
  sc_biguint<8> c_97405;
  sc_biguint<8> c_97414;
  sc_biguint<4> c_97393;
  bool c_97396;
  sc_biguint<8> c_97389;
  sc_biguint<8> c_97398;
  sc_biguint<4> c_97377;
  bool c_97380;
  sc_biguint<8> c_97373;
  sc_biguint<8> c_97382;
  sc_biguint<4> c_97361;
  bool c_97364;
  sc_biguint<8> c_97357;
  sc_biguint<8> c_97366;
  sc_biguint<4> c_97345;
  bool c_97348;
  sc_biguint<8> c_97341;
  sc_biguint<8> c_97350;
  sc_biguint<4> c_97329;
  bool c_97332;
  sc_biguint<8> c_97325;
  sc_biguint<8> c_97334;
  sc_biguint<4> c_97313;
  bool c_97316;
  sc_biguint<8> c_97309;
  sc_biguint<8> c_97318;
  sc_biguint<4> c_97297;
  bool c_97300;
  sc_biguint<8> c_97293;
  sc_biguint<8> c_97302;
  sc_biguint<4> c_97281;
  bool c_97284;
  sc_biguint<8> c_97277;
  sc_biguint<8> c_97286;
  sc_biguint<4> c_97265;
  bool c_97268;
  sc_biguint<8> c_97261;
  sc_biguint<8> c_97270;
  sc_biguint<4> c_97249;
  bool c_97252;
  sc_biguint<8> c_97245;
  sc_biguint<8> c_97254;
  sc_biguint<4> c_97239;
  bool c_97242;
  sc_biguint<8> c_97235;
  sc_biguint<8> c_97244;
  sc_biguint<16> c_97259;
  sc_biguint<24> c_97275;
  sc_biguint<32> c_97291;
  sc_biguint<40> c_97307;
  sc_biguint<48> c_97323;
  sc_biguint<56> c_97339;
  sc_biguint<64> c_97355;
  sc_biguint<72> c_97371;
  sc_biguint<80> c_97387;
  sc_biguint<88> c_97403;
  sc_biguint<96> c_97419;
  sc_biguint<104> c_97435;
  sc_biguint<112> c_97451;
  sc_biguint<120> c_97467;
  sc_biguint<128> c_97483;
  sc_biguint<2> decode_97224_update_TEST_status();
  bool c_97489;
  sc_biguint<2> c_97491;
  sc_biguint<128> decode_97501_update_ENCRYPT_enc_data();
  const c_97503[16] = {0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  sc_biguint<128> c_97511;
  sc_biguint<128> c_97513;
  sc_biguint<128> c_97507;
  sc_biguint<128> c_97514;
  sc_biguint<128> c_97505;
  sc_biguint<128> c_97515;
  sc_biguint<128> process128(sc_biguint<128> arg_0, sc_biguint<128> arg_1);
  sc_biguint<128> c_97516;
  sc_biguint<128> c_97517;
  sc_biguint<2> decode_97501_update_TEST_status();
  void ite_97685(std::map<int, int>& mem_update_map);
  sc_biguint<16> c_97527;
  sc_biguint<16> c_97525;
  sc_biguint<16> c_97528;
  sc_biguint<4> c_97678;
  bool c_97681;
  sc_biguint<8> c_97674;
  sc_biguint<4> c_97668;
  bool c_97671;
  sc_biguint<8> c_97664;
  sc_biguint<4> c_97658;
  bool c_97661;
  sc_biguint<8> c_97654;
  sc_biguint<4> c_97648;
  bool c_97651;
  sc_biguint<8> c_97644;
  sc_biguint<4> c_97638;
  bool c_97641;
  sc_biguint<8> c_97634;
  sc_biguint<4> c_97628;
  bool c_97631;
  sc_biguint<8> c_97624;
  sc_biguint<4> c_97618;
  bool c_97621;
  sc_biguint<8> c_97614;
  sc_biguint<4> c_97608;
  bool c_97611;
  sc_biguint<8> c_97604;
  sc_biguint<4> c_97598;
  bool c_97601;
  sc_biguint<8> c_97594;
  sc_biguint<4> c_97588;
  bool c_97591;
  sc_biguint<8> c_97584;
  sc_biguint<4> c_97578;
  bool c_97581;
  sc_biguint<8> c_97574;
  sc_biguint<4> c_97568;
  bool c_97571;
  sc_biguint<8> c_97564;
  sc_biguint<4> c_97558;
  bool c_97561;
  sc_biguint<8> c_97554;
  sc_biguint<4> c_97548;
  bool c_97551;
  sc_biguint<8> c_97544;
  sc_biguint<4> c_97538;
  bool c_97541;
  sc_biguint<8> c_97534;
  sc_biguint<8> c_97532;
  sc_biguint<8> c_97543;
  sc_biguint<8> c_97553;
  sc_biguint<8> c_97563;
  sc_biguint<8> c_97573;
  sc_biguint<8> c_97583;
  sc_biguint<8> c_97593;
  sc_biguint<8> c_97603;
  sc_biguint<8> c_97613;
  sc_biguint<8> c_97623;
  sc_biguint<8> c_97633;
  sc_biguint<8> c_97643;
  sc_biguint<8> c_97653;
  sc_biguint<8> c_97663;
  sc_biguint<8> c_97673;
  sc_biguint<8> c_97683;
  std::map<int, int> decode_97523_update_TEST_XRAM_map;
  void decode_97523_update_TEST_XRAM(std::map<int, int>& mem_update_map);
  sc_biguint<16> decode_97523_update_ENCRYPT_blk_cnt();
  bool c_97697;
  sc_biguint<16> c_97691;
  bool c_97692;
  sc_biguint<16> c_97688;
  sc_biguint<16> c_97694;
  sc_biguint<16> c_97699;
  sc_biguint<4> decode_97523_update_ENCRYPT_byte_cnt();
  sc_biguint<4> c_97531;
  sc_biguint<2> decode_97523_update_TEST_status();
  bool c_97712;
  sc_biguint<16> c_97706;
  bool c_97707;
  sc_biguint<2> c_97709;
  sc_biguint<2> c_97714;
  void compute();
  SC_HAS_PROCESS(TEST);
  TEST(sc_module_name name_) : sc_module(name_) {
    SC_METHOD(compute);
    sensitive << TEST_cmd_in << TEST_cmdaddr_in << TEST_cmddata_in << TEST_cmdflag_in;
  }
};