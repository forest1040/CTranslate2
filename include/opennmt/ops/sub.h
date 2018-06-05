#pragma once

#include "opennmt/ops/op.h"

namespace opennmt {
  namespace ops {

    class Sub : public BinaryOp {
    public:
      void operator()(const StorageView& a, const StorageView& b, StorageView& c) const override {
        TYPE_DISPATCH(a.dtype(), compute<T>(a, b, c));
      }

    private:
      template <typename T>
      void compute(const StorageView& a, const StorageView& b, StorageView& c) const {
        if (b.is_scalar()) {
          c = a;
          primitives::sub(b.data<T>()[0], c.data<T>(), c.size());
        } else {
          c.resize_as(a);
          primitives::sub(a.data<T>(), b.data<T>(), c.data<T>(), c.size());
        }
      }
    };

  }
}
