/// \file
/// Unit test for hashing ast sub-trees

#include "unit-include/util.h"
#include <ilang/ila/instr_lvl_abs.h>

namespace ilang {

using namespace ExprFuse;

class TestHashApi : public ::testing::Test {
public:
  TestHashApi() {
    ila = InstrLvlAbs::New("host");
    x = ila->NewBoolState("x");
    y = ila->NewBoolState("y");
    z = ila->NewBoolState("z");
    bv_x = ila->NewBvState("bv_x", 8);
    bv_y = ila->NewBvState("bv_y", 8);
    bv_z = ila->NewBvState("bv_z", 8);
    mngr = ila->expr_mngr();
    if (!mngr) // XXX make it better
      mngr = ExprMngr::New();
  }

  ~TestHashApi() {}

  void SetUp() {
    DebugLog::Enable("HashApi");
    // SetToStdErr(1);
  }

  void TearDown() {
    DebugLog::Disable("HashApi");
    // SetToStdErr(0);
  }

  InstrLvlAbsPtr ila = NULL;
  ExprPtr x = NULL;
  ExprPtr y = NULL;
  ExprPtr z = NULL;
  ExprPtr bv_x = NULL;
  ExprPtr bv_y = NULL;
  ExprPtr bv_z = NULL;
  ExprMngrPtr mngr = NULL;

}; // TestHashApi

TEST_F(TestHashApi, level0) {
  // bool const
  auto a = BoolConst(true);
  auto b = BoolConst(true);
  auto c = BoolConst(false);

  auto sa = mngr->GetRep(a);
  auto sb = mngr->GetRep(b);
  auto sc = mngr->GetRep(c);

  EXPECT_EQ(sa, sb);
  EXPECT_NE(sa, sc);

  // bv const
  a = BvConst(0, 8);
  b = BvConst(0, 8);
  c = BvConst(1, 8);

  sa = mngr->GetRep(a);
  sb = mngr->GetRep(b);
  sc = mngr->GetRep(c);

  EXPECT_EQ(sa, sb);
  EXPECT_NE(sa, sc);

  // mem const (not shared)
  a = MemConst(0, 8, 8);
  b = MemConst(0, 8, 8);

  sa = mngr->GetRep(a);
  sb = mngr->GetRep(b);

  EXPECT_NE(sa, sb);
}

TEST_F(TestHashApi, level1) {
  // binary
  auto a = And(x, y);
  auto b = And(x, y);

  auto sa = mngr->GetRep(a);
  auto sb = mngr->GetRep(b);

  EXPECT_EQ(sa, sb);

  // ternary
  a = Ite(x, y, z);
  b = Ite(x, y, z);

  sa = mngr->GetRep(a);
  sb = mngr->GetRep(b);

  EXPECT_EQ(sa, sb);

  // param
  a = Extract(bv_x, 4, 0);
  b = Extract(bv_x, 4, 0);
  auto c = Extract(bv_y, 4, 0);
  auto d = Extract(bv_y, 3, 0);

  sa = mngr->GetRep(a);
  sb = mngr->GetRep(b);
  auto sc = mngr->GetRep(c);
  auto sd = mngr->GetRep(d);

  EXPECT_EQ(sa, sb);
  EXPECT_NE(sa, sc);
  EXPECT_NE(sa, sd);
  EXPECT_NE(sc, sd);
}

TEST_F(TestHashApi, level2) {
  auto a = And(x, y);
  auto b = Or(a, z);

  auto c = And(x, y);
  auto d = Or(c, z);

  auto sb = mngr->GetRep(b);
  auto sd = mngr->GetRep(d);

  EXPECT_EQ(sb, sd);

  auto e = Xor(x, y);
  auto f = Or(e, z);

  auto sf = mngr->GetRep(f);

  EXPECT_NE(sb, sf);
}

TEST_F(TestHashApi, ExplicitName) {
  auto bad_name = ila->NewBvState("ADDbv_xbv_y", 8);
  auto same_name = Add(x, y);

  auto rb = mngr->GetRep(bad_name);
  auto rs = mngr->GetRep(same_name);

  EXPECT_NE(rb, rs);
}

#if 0
// Below are the tables used in AES
// if you use two different variables
// to index into the two tables, there
// should not be replacement between the two
// and let's see if this is true

unsigned S_table[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
    0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
    0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
    0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
    0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
    0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
    0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
    0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
    0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
    0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
    0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
    0xb0, 0x54, 0xbb, 0x16};

unsigned xS_table[256] = {
    0xc6, 0xf8, 0xee, 0xf6, 0xff, 0xd6, 0xde, 0x91, 0x60, 0x02, 0xce, 0x56,
    0xe7, 0xb5, 0x4d, 0xec, 0x8f, 0x1f, 0x89, 0xfa, 0xef, 0xb2, 0x8e, 0xfb,
    0x41, 0xb3, 0x5f, 0x45, 0x23, 0x53, 0xe4, 0x9b, 0x75, 0xe1, 0x3d, 0x4c,
    0x6c, 0x7e, 0xf5, 0x83, 0x68, 0x51, 0xd1, 0xf9, 0xe2, 0xab, 0x62, 0x2a,
    0x08, 0x95, 0x46, 0x9d, 0x30, 0x37, 0x0a, 0x2f, 0x0e, 0x24, 0x1b, 0xdf,
    0xcd, 0x4e, 0x7f, 0xea, 0x12, 0x1d, 0x58, 0x34, 0x36, 0xdc, 0xb4, 0x5b,
    0xa4, 0x76, 0xb7, 0x7d, 0x52, 0xdd, 0x5e, 0x13, 0xa6, 0xb9, 0x00, 0xc1,
    0x40, 0xe3, 0x79, 0xb6, 0xd4, 0x8d, 0x67, 0x72, 0x94, 0x98, 0xb0, 0x85,
    0xbb, 0xc5, 0x4f, 0xed, 0x86, 0x9a, 0x66, 0x11, 0x8a, 0xe9, 0x04, 0xfe,
    0xa0, 0x78, 0x25, 0x4b, 0xa2, 0x5d, 0x80, 0x05, 0x3f, 0x21, 0x70, 0xf1,
    0x63, 0x77, 0xaf, 0x42, 0x20, 0xe5, 0xfd, 0xbf, 0x81, 0x18, 0x26, 0xc3,
    0xbe, 0x35, 0x88, 0x2e, 0x93, 0x55, 0xfc, 0x7a, 0xc8, 0xba, 0x32, 0xe6,
    0xc0, 0x19, 0x9e, 0xa3, 0x44, 0x54, 0x3b, 0x0b, 0x8c, 0xc7, 0x6b, 0x28,
    0xa7, 0xbc, 0x16, 0xad, 0xdb, 0x64, 0x74, 0x14, 0x92, 0x0c, 0x48, 0xb8,
    0x9f, 0xbd, 0x43, 0xc4, 0x39, 0x31, 0xd3, 0xf2, 0xd5, 0x8b, 0x6e, 0xda,
    0x01, 0xb1, 0x9c, 0x49, 0xd8, 0xac, 0xf3, 0xcf, 0xca, 0xf4, 0x47, 0x10,
    0x6f, 0xf0, 0x4a, 0x5c, 0x38, 0x57, 0x73, 0x97, 0xcb, 0xa1, 0xe8, 0x3e,
    0x96, 0x61, 0x0d, 0x0f, 0xe0, 0x7c, 0x71, 0xcc, 0x90, 0x06, 0xf7, 0x1c,
    0xc2, 0x6a, 0xae, 0x69, 0x17, 0x99, 0x3a, 0x27, 0xd9, 0xeb, 0x2b, 0x22,
    0xd2, 0xa9, 0x07, 0x33, 0x2d, 0x3c, 0x15, 0xc9, 0x87, 0xaa, 0x50, 0xa5,
    0x03, 0x59, 0x09, 0x1a, 0x65, 0xd7, 0x84, 0xd0, 0x82, 0x29, 0x5a, 0x1e,
    0x7b, 0xa8, 0x6d, 0x2c};

ExprPtr s_table_read(const ExprPtr& idx) {
  //assert(idx.bit_width() == 8);

  ExprPtr ret = BvConst(S_table[0], 8);
  for (int i = 1; i < 256; i++)
    ret = Ite(
      Eq(idx, BvConst(i,8)), 
      BvConst(S_table[i], 8), 
      ret);
  return ret;
}

ExprPtr xs_table_read(const ExprPtr& idx) {
  //assert(idx.bit_width() == 8);

  ExprPtr ret = BvConst(xS_table[0], 8);
  for (int i = 1; i < 256; i++)
    ret = Ite(
      Eq(idx, BvConst(i,8)),
      BvConst(xS_table[i], 8), 
      ret);
  return ret;
}

TEST_F(TestHashApi, HashConflict) {
  std::set<ExprPtr> avoid_gc;
  std::set<Expr *> Aptrs;

  auto insert_to_A_set = [&Aptrs] (const ExprPtr & n) -> void {
    if(n->is_op())
      Aptrs.insert(n.get()); // not the vars/constants
  };

  auto check_not_exists_in_A_set = [&] (const ExprPtr & n) -> void {
    if(n->is_op())
      EXPECT_EQ( Aptrs.find(n.get()) , Aptrs.end() );
  };


  for(unsigned t = 0; t < 10000; t++) {
    Aptrs.clear();

    auto iA = ila->NewBvState("iA" + std::to_string(t), 8);
    auto iB = ila->NewBvState("iB" + std::to_string(t), 8);
    auto tA = s_table_read(iA);
    auto tB = xs_table_read(iB);
    auto rA = mngr->GetRep(tA);
    auto rB = mngr->GetRep(tB);


    rA->DepthFirstVisit(insert_to_A_set);
    rB->DepthFirstVisit(check_not_exists_in_A_set);

    avoid_gc.insert(rA); // do this iteratively
    avoid_gc.insert(rB);

    if(t%100 == 0)
      ILA_INFO<<"Count:"<<t;
  }

}
#endif

} // namespace ilang
