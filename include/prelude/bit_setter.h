#pragma once

namespace pre {

class BitSetter {
  BitSetter(const BitSetter&);
  void operator=(const BitSetter&);
  static const uint32_t kMaxBits = 31;
  static const uint32_t kBitSeries[] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
    1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912,
    1073741824, 2147483648
  };
 public:
  BitSetter() : bits_(nullptr), size_(kMaxBits) {}
  ~BitSetter() { Dispose(); }

  void Set(uint32_t bit_position) {
    if (bit_position > size_) {
      uint32_t old_num_ints = (size_ / kMaxBits);
      uint32_t old_num_bytes = old_num_ints * sizeof(uint32_t);
      uint32_t num_ints = (bit_position / kMaxBits) + 1;
      uint32_t num_bytes = num_ints * sizeof(uint32_t);

      bits_ = (uint32_t*)realloc(bits_, num_bytes); 
      memset(bits_ + old_num_ints, 0, num_bytes - old_num_bytes);
      size_ = num_ints * kMaxBits;
    } else if (!bits_) {
      bits_ = (uint32_t*)malloc(sizeof(uint32_t));
      memset(bits_, 0, sizeof(uint32_t));
    }

    if (bit_position > kMaxBits) {
      bits_[bit_position / kMaxBits] |= kBitSeries[bit_position - size_];
    } else {
      bits_[0] |= kBitSeries[bit_position];
    }
  }

  void Set(uint32_t bit_position, bool setting) {
    setting ? set(bit_position) : unset(bit_position);
  }

  void Unset(uint32_t bit_position) {
    if (bit_position > kMaxBits) {
      bits_[bit_position / kMaxBits] &= ~kBitSeries[bit_position - size_];
    } else {
      bits_[0] &= ~kBitSeries[bit_position];
    }
  }

  void RawSet(uint32_t dword_position, uint32_t value) {
    uint32_t num_ints = (size_ / kMaxBits);
    uint32_t num_bytes = num_ints * sizeof(uint32_t);

    if (dword_position >= num_ints) {
      uint32_t new_num_bytes = (dword_position + 1) * sizeof(uint32_t);
      bits_ = (uint32_t*)realloc(bits_, new_num_bytes); 
      memset(bits_ + num_bytes, 0, new_num_bytes - num_bytes);
    } else if (!bits_) {
      bits_ = (uint32_t*)malloc(sizeof(uint32_t));
      memset(bits_, 0, sizeof(uint32_t));
    }

    bits_[dword_position] = value;
  }

  void Toggle(uint32_t bit_position) {
    if (bit_position > kMaxBits) {
      bits_[bit_position / kMaxBits] ^= kBitSeries[bit_position - size_];
    } else {
      bits_[0] ^= kBitSeries[bit_position];
    }
  }

  bool IsSet(uint32_t bit_position) const { // I wonder if there's a way to make this faster
    assert(bit_position <= size_);
    if (bit_position > kMaxBits) {
      // bit_position / kMaxBits gets the index we're working with, e.g., 64/31 = index 2
      return (bits_[bit_position / kMaxBits] & kBitSeries[bit_position - size_]) != 0;
    }
    return (bits_[0] & kBitSeries[bit_position]) != 0;
  }

  void Dispose() {
    if (bits_) {
      free(bits_);
      bits_ = 0;
    }
  }

  void CopyFrom(const BitSetter& other) {
    uint32_t num_bytes = (other.size_ / kMaxBits) * sizeof(uint32_t);

    size_ = other.size_;
    bits_ = (uint32_t*)malloc(num_bytes);
    memcpy(bits_, other.bits_, num_bytes);
  }

 private:
  uint32_t* bits_;
  uint32_t size_;
};

} // namespace pre
