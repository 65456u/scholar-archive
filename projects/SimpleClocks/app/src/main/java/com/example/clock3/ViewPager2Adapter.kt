package com.example.clock3

import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentActivity
import androidx.viewpager2.adapter.FragmentStateAdapter

internal class ViewPager2Adapter(fa: FragmentActivity) : FragmentStateAdapter(fa) {

    override fun getItemCount(): Int {
        return 2 // 两个页面：图形时钟和数字时钟
    }

    override fun createFragment(position: Int): Fragment {
        return when (position) {
            0 -> AnalogClockFragment() // 第一个页面是图形时钟
            1 -> DigitalClockFragment() // 第二个页面是数字时钟
            else -> throw IllegalStateException("Unexpected position: $position")
        }
    }
}
