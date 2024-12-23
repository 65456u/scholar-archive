package com.example.clock3

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.fragment.app.FragmentActivity
import androidx.viewpager2.widget.ViewPager2

class MainActivity : FragmentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val viewPager2: ViewPager2 = findViewById(R.id.viewpager)
        viewPager2.adapter = ViewPager2Adapter(this) // 设置适配器
    }
}
