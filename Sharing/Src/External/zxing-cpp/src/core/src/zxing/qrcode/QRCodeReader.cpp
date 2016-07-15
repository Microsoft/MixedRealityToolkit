// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  QRCodeReader.cpp
 *  zxing
 *
 *  Created by Christian Brunschen on 20/05/2008.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/qrcode/detector/Detector.h>

#include <iostream>

namespace zxing {
	namespace qrcode {
		
		using namespace std;
		
		QRCodeReader::QRCodeReader() :decoder_() {
		}
		//TODO: see if any of the other files in the qrcode tree need tryHarder
		Ref<Result> QRCodeReader::decode(Ref<BinaryBitmap> image, DecodeHints hints) {
			Detector detector(image->getBlackMatrix());
			Ref<DetectorResult> detectorResult(detector.detect(hints));

			/// MICROSOFT PROJECT B CHANGES BEGIN
			if (!detectorResult.empty())
			{
			/// MICROSOFT PROJECT B CHANGES END
				ArrayRef< Ref<ResultPoint> > points(detectorResult->getPoints());
				Ref<DecoderResult> decoderResult(decoder_.decode(detectorResult->getBits()));
				Ref<Result> result(new Result(decoderResult->getText(), decoderResult->getRawBytes(), points, BarcodeFormat::QR_CODE));
				return result;
			/// MICROSOFT PROJECT B CHANGES BEGIN
			}
			else
			{
				return Ref<Result>();
			}
			/// MICROSOFT PROJECT B CHANGES END
		}
		
		QRCodeReader::~QRCodeReader() {
		}
		
    Decoder& QRCodeReader::getDecoder() {
        return decoder_;
    }
	}
}
