/*
 * Copyright (C) 2006 The Android Open Source Project
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
#include <animation/animation.h>
namespace SOUI {
	/**
	 * An animation that controls the scale of an object. You can specify the point
	 * to use for the center of scaling.
	 *
	 */
	class SOUI_EXP SScaleAnimation : public SAnimation {
	SOUI_CLASS_NAME(SScaleAnimation,L"scale")

		private: float mFromX;
		private: float mToX;
		private: float mFromY;
		private: float mToY;

		private: ValueType mPivotXType;
		private: ValueType mPivotYType;
		private: float mPivotXValue;
		private: float mPivotYValue;

		private: float mPivotX;
		private: float mPivotY;


		/**
		 * Constructor to use when building a ScaleAnimation from code
		 *
		 * @param fromX Horizontal scaling factor to apply at the start of the
		 *        animation
		 * @param toX Horizontal scaling factor to apply at the end of the animation
		 * @param fromY Vertical scaling factor to apply at the start of the
		 *        animation
		 * @param toY Vertical scaling factor to apply at the end of the animation
		 */
		public: SScaleAnimation(float fromX=0.0f, float toX = 0.0f, float fromY = 0.0f, float toY = 0.0f) {
			mFromX = fromX;
			mToX = toX;
			mFromY = fromY;
			mToY = toY;
			mPivotX = 0;
			mPivotY = 0;
		}

		/**
		 * Constructor to use when building a ScaleAnimation from code
		 *
		 * @param fromX Horizontal scaling factor to apply at the start of the
		 *        animation
		 * @param toX Horizontal scaling factor to apply at the end of the animation
		 * @param fromY Vertical scaling factor to apply at the start of the
		 *        animation
		 * @param toY Vertical scaling factor to apply at the end of the animation
		 * @param pivotX The X coordinate of the point about which the object is
		 *        being scaled, specified as an absolute number where 0 is the left
		 *        edge. (This point remains fixed while the object changes size.)
		 * @param pivotY The Y coordinate of the point about which the object is
		 *        being scaled, specified as an absolute number where 0 is the top
		 *        edge. (This point remains fixed while the object changes size.)
		 */
		public: SScaleAnimation(float fromX, float toX, float fromY, float toY,
			float pivotX, float pivotY) {
			mFromX = fromX;
			mToX = toX;
			mFromY = fromY;
			mToY = toY;

			mPivotXType = ABSOLUTE_VALUE;
			mPivotYType = ABSOLUTE_VALUE;
			mPivotXValue = pivotX;
			mPivotYValue = pivotY;
			initializePivotPoint();
		}

		/**
		 * Constructor to use when building a ScaleAnimation from code
		 *
		 * @param fromX Horizontal scaling factor to apply at the start of the
		 *        animation
		 * @param toX Horizontal scaling factor to apply at the end of the animation
		 * @param fromY Vertical scaling factor to apply at the start of the
		 *        animation
		 * @param toY Vertical scaling factor to apply at the end of the animation
		 * @param pivotXType Specifies how pivotXValue should be interpreted. One of
		 *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
		 *        Animation.RELATIVE_TO_PARENT.
		 * @param pivotXValue The X coordinate of the point about which the object
		 *        is being scaled, specified as an absolute number where 0 is the
		 *        left edge. (This point remains fixed while the object changes
		 *        size.) This value can either be an absolute number if pivotXType
		 *        is ABSOLUTE, or a percentage (where 1.0 is 100%) otherwise.
		 * @param pivotYType Specifies how pivotYValue should be interpreted. One of
		 *        Animation.ABSOLUTE, Animation.RELATIVE_TO_SELF, or
		 *        Animation.RELATIVE_TO_PARENT.
		 * @param pivotYValue The Y coordinate of the point about which the object
		 *        is being scaled, specified as an absolute number where 0 is the
		 *        top edge. (This point remains fixed while the object changes
		 *        size.) This value can either be an absolute number if pivotYType
		 *        is ABSOLUTE, or a percentage (where 1.0 is 100%) otherwise.
		 */
		public: SScaleAnimation(float fromX, float toX, float fromY, float toY,
			ValueType pivotXType, float pivotXValue, ValueType pivotYType, float pivotYValue) {
			mFromX = fromX;
			mToX = toX;
			mFromY = fromY;
			mToY = toY;

			mPivotXValue = pivotXValue;
			mPivotXType = pivotXType;
			mPivotYValue = pivotYValue;
			mPivotYType = pivotYType;
			initializePivotPoint();
		}

		/**
		 * Called at the end of constructor methods to initialize, if possible, values for
		 * the pivot point. This is only possible for ABSOLUTE pivot values.
		 */
		private: void initializePivotPoint() {
			if (mPivotXType == ABSOLUTE_VALUE) {
				mPivotX = mPivotXValue;
			}
			if (mPivotYType == ABSOLUTE_VALUE) {
				mPivotY = mPivotYValue;
			}
		}

	protected:
	void applyTransformation(float interpolatedTime, Transformation & t) {
			float sx = 1.0f;
			float sy = 1.0f;
			float scale = getScaleFactor();

			if (mFromX != 1.0f || mToX != 1.0f) {
				sx = mFromX + ((mToX - mFromX) * interpolatedTime);
			}
			if (mFromY != 1.0f || mToY != 1.0f) {
				sy = mFromY + ((mToY - mFromY) * interpolatedTime);
			}

			if (mPivotX == 0 && mPivotY == 0) {
				t.getMatrix().setScale(sx, sy);
			}
			else {
				t.getMatrix().setScale(sx, sy, scale * mPivotX, scale * mPivotY);
			}
			t.setTransformationType(Transformation::TYPE_MATRIX);
	}

	void copy(const IAnimation *src) override
	{
		SAnimation::copy(src);
		const SScaleAnimation * src2 = sobj_cast<const SScaleAnimation>(src);
		mFromX = src2->mFromX;
		mToX = src2->mToX;
		mFromY = src2->mFromY;
		mToY = src2->mToY;
		mPivotXType = src2->mPivotXType;
		mPivotXValue = src2->mPivotXValue;
		mPivotYType = src2->mPivotYType;
		mPivotYValue = src2->mPivotYValue;
	}
		public: void initialize(int width, int height, int parentWidth, int parentHeight) {
			mPivotX = (float)resolveSize(mPivotXType, mPivotXValue, width, parentWidth);
			mPivotY = (float)resolveSize(mPivotYType, mPivotYValue, height, parentHeight);
		}

				SOUI_ATTRS_BEGIN()
					ATTR_FLOAT(L"fromXScale",mFromX,FALSE)
					ATTR_FLOAT(L"toXScale", mToX, FALSE)
					ATTR_FLOAT(L"fromYScale", mFromY, FALSE)
					ATTR_FLOAT(L"toYScale", mToY, FALSE)
					ATTR_VALUE_DESC(L"pivotX",mPivotXType,mPivotXValue)
					ATTR_VALUE_DESC(L"pivotY", mPivotYType, mPivotYValue)
				SOUI_ATTRS_END()
	};

}