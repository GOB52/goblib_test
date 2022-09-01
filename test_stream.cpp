/*
  Unittest for stream
*/
#include "gtest/gtest.h"
#include <gob_memory_stream.hpp>
#include <gob_utility.hpp> // goblib::size
#include <gob_endianness.hpp> // goblib::endian

TEST(Stream, MemoryStream)
{
    //    printf("little:%d big:%d other:%d\n", goblib::endian::little, goblib::endian::big, goblib::endian::other);
    {
        char buffer[] = "abcdefghijklmnopqrstuvwxyz";
        goblib::MemoryStream ss(buffer, sizeof(buffer)-1);

        EXPECT_TRUE(ss.is_open());

        EXPECT_TRUE(ss.seek(0, goblib::seekdir::end));
        EXPECT_EQ(26U, ss.position());

        EXPECT_TRUE(ss.seek(0, goblib::seekdir::beg));
        EXPECT_EQ(0U, ss.position());
        EXPECT_FALSE(ss.seek(-123, goblib::seekdir::beg));
        EXPECT_EQ(0U, ss.position());
    
        auto d8 = ss.read8();
        EXPECT_EQ(d8, 'a');
        EXPECT_EQ(1U, ss.position());

        EXPECT_TRUE(ss.seek(5, goblib::seekdir::cur));
        d8 = ss.read8();
        EXPECT_EQ(d8, 'g');
        EXPECT_EQ(7U, ss.position());

        EXPECT_TRUE(ss.seek(-7, goblib::seekdir::cur));
        EXPECT_EQ(0U, ss.position());
        EXPECT_FALSE(ss.seek(-7, goblib::seekdir::cur));
        EXPECT_EQ(0U, ss.position());

        d8 = ss.read8();
        EXPECT_EQ(d8, 'a');
        EXPECT_EQ(1U, ss.position());

        EXPECT_FALSE(ss.seek(1000, goblib::seekdir::cur));
        EXPECT_EQ(1U, ss.position());
        EXPECT_TRUE(ss.seek(0, goblib::seekdir::end));
        EXPECT_EQ(26U, ss.position());
        EXPECT_FALSE(ss.seek(-10000, goblib::seekdir::end));
        EXPECT_EQ(26U, ss.position());
        EXPECT_TRUE(ss.seek(-8, goblib::seekdir::end));
        EXPECT_EQ(26U-8U, ss.position());
    
        EXPECT_TRUE(ss.seek(10, goblib::seekdir::beg));
        EXPECT_EQ(10U, ss.position());
    
        auto d16 = ss.read16();
        if(goblib::endian::little)  { EXPECT_EQ(0x6C6BU, d16); }
        else if(goblib::endian::big){ EXPECT_EQ(0x6B6CU, d16); }
        EXPECT_EQ(12U, ss.position());

        auto d32 = ss.read32();
        if(goblib::endian::little)  { EXPECT_EQ(0x706F6E6DU, d32); }
        else if(goblib::endian::big){ EXPECT_EQ(0x6D6E6F70U, d32); }
        EXPECT_EQ(16U, ss.position());
    }

    //
    {
        std::uint32_t buffer32[8] = {0,1,2,3,4,5,6,7};
        goblib::MemoryStream s32(buffer32, goblib::size(buffer32));
        s32.seek(0, goblib::seekdir::end);
        EXPECT_EQ(sizeof(buffer32), s32.position());
          
        s32.seek(0, goblib::seekdir::beg);
        auto d32 = s32.read32();
        EXPECT_EQ(0U, d32);
        d32 = s32.read32();
        EXPECT_EQ(1U, d32);

        auto d16 = s32.read16();
        if(goblib::endian::little)  { EXPECT_EQ(2U, d16); }
        else if(goblib::endian::big){ EXPECT_EQ(0U, d16); }
        d16 = s32.read16();
        if(goblib::endian::little)  { EXPECT_EQ(0U, d16); }
        else if(goblib::endian::big){ EXPECT_EQ(2U, d16); }
    }
    
    //
    {
        std::array<std::int8_t, 10> c_array = { 0, 11,22,33,44,55,66,77,88,99 };
        std::int8_t c_array_copy[10] = {};
        goblib::MemoryStream sarray(c_array);
        sarray.seek(0, goblib::seekdir::end);
        EXPECT_EQ(sizeof(c_array), sarray.position());

        sarray.seek(0, goblib::seekdir::beg);
        sarray.read(c_array_copy, sizeof(c_array_copy));
        EXPECT_TRUE(std::memcmp(c_array.data(), c_array_copy, sizeof(c_array_copy)) == 0);
    }

    //
    {
        std::vector<std::int16_t> c_vector(16, 42);
        goblib::MemoryStream svector(c_vector);
        std::int16_t c_vector_copy[16] = {};
        svector.seek(0, goblib::seekdir::end);
        EXPECT_EQ(sizeof(decltype(c_vector)::value_type) * c_vector.size(), svector.position());
          
        svector.seek(0, goblib::seekdir::beg);
        svector.read(c_vector_copy, sizeof(c_vector_copy));
        EXPECT_TRUE(std::memcmp(c_vector.data(), c_vector_copy, sizeof(c_vector_copy)) == 0);
    }
    

    {
        int dummy;
        goblib::MemoryStream zero(&dummy, 0);
    
        EXPECT_TRUE(zero.is_open());
        EXPECT_EQ(0U, zero.position());

        zero.seek(1, goblib::seekdir::beg);
        EXPECT_EQ(0U, zero.position());
        zero.seek(-1, goblib::seekdir::beg);
        EXPECT_EQ(0U, zero.position());

        zero.seek(1, goblib::seekdir::cur);
        EXPECT_EQ(0U, zero.position());
        zero.seek(-1, goblib::seekdir::cur);
        EXPECT_EQ(0U, zero.position());
          
        zero.seek(1, goblib::seekdir::end);
        EXPECT_EQ(0U, zero.position());
        zero.seek(-1, goblib::seekdir::end);
        EXPECT_EQ(0U, zero.position());
    }


    {
        struct A { std::uint32_t dw[8]; std::uint16_t w[16]; std::uint8_t b[32]; };
        A a = {{1,}, {2,}, {3,} };
        goblib::MemoryStream file(&a, sizeof(A));
    
        A aout;
        EXPECT_EQ(file.read(&aout, sizeof(aout)), sizeof(aout));
        EXPECT_TRUE(std::memcmp(&aout, &a, sizeof(a)) == 0);
    }

    
    // Compoile error
#if 0
    {
        int aaa;
        goblib::MemoryStream err0(aaa,1); // not pointer!
    }
#endif

}
