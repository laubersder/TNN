// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "tnn/device/x86/acc/x86_layer_acc.h"
#include "tnn/device/x86/x86_device.h"
#include "tnn/device/x86/acc/x86_reduce_op_layer_acc.h"

#include <vector>
#include <cmath>
#include <immintrin.h>

namespace TNN_NS {

typedef struct x86_reduce_prod_operator : x86_reduce_operator {
#ifdef __AVX2__
    __m256 Init() {
        return _mm256_set1_ps(1.f);
    }
    __m256 operator()(const __m256 v1_, const __m256 v2_) {
        return _mm256_mul_ps(v1_, v2_);
    }
#else
    float Init() { return 1.0f; }
    float operator()(const float v1, const float v2) {
        return v1 * v2;
    }

#endif
} X86_REDUCE_PROD_OP;

DECLARE_X86_REDUCE_OP_ACC(ReduceProd, X86_REDUCE_PROD_OP);

REGISTER_X86_ACC(ReduceProd, LAYER_REDUCE_PROD);

}   // namespace TNN_NS

