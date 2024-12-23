package com.example.clock3

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.util.AttributeSet
import android.view.View
import kotlin.math.cos
import kotlin.math.min
import kotlin.math.sin

class ClockView(context: Context, attrs: AttributeSet? = null) : View(context, attrs) {
    private val paint = Paint().apply {
        isAntiAlias = true
    }
    private var radius = 0f
    private var centerX = 0f
    private var centerY = 0f

    private fun setupMeasurements() {
        radius = min(width, height) / 2 * 0.8f
        centerX = width / 2f
        centerY = height / 2f
    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)
        setupMeasurements()
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        drawClockFace(canvas)
        drawHands(canvas)
    }

    private fun drawClockFace(canvas: Canvas) {
        paint.color = Color.BLACK
        paint.strokeWidth = 8f
        paint.style = Paint.Style.STROKE
        canvas.drawCircle(centerX, centerY, radius, paint)

        // Draw clock hour marks
        for (i in 0..11) {
            val angle = Math.PI / 6 * i
            val lineLength = if (i % 3 == 0) 30f else 15f
            val startX = centerX + radius * cos(angle).toFloat()
            val startY = centerY + radius * sin(angle).toFloat()
            val stopX = centerX + (radius - lineLength) * cos(angle).toFloat()
            val stopY = centerY + (radius - lineLength) * sin(angle).toFloat()
            canvas.drawLine(startX, startY, stopX, stopY, paint)
        }
    }

    private fun drawHands(canvas: Canvas) {
        val calendar = java.util.Calendar.getInstance()
        val milliSecond = calendar.get(java.util.Calendar.MILLISECOND)
        val second = calendar.get(java.util.Calendar.SECOND) + milliSecond / 1000f
        val minute = calendar.get(java.util.Calendar.MINUTE) + second / 60
        val hour = calendar.get(java.util.Calendar.HOUR_OF_DAY) + minute / 60

        // Hour hand
        drawHand(canvas, hour * 5, true)  // Multiply by 5 to scale to clock face
        // Minute hand
        drawHand(canvas, minute, false)
        // Second hand
        paint.color = Color.RED
        drawHand(canvas, second, false)
    }

    private fun drawHand(canvas: Canvas, loc: Float, isHour: Boolean) {
        val angle = Math.PI * loc / 30 - Math.PI / 2
        val handRadius = if (isHour) radius * 0.5f else radius * 0.7f
        paint.strokeWidth = if (isHour) 16f else 10f
        canvas.drawLine(
            centerX,
            centerY,
            centerX + handRadius * cos(angle).toFloat(),
            centerY + handRadius * sin(angle).toFloat(),
            paint
        )
    }

    init {
        val ticker = object : Runnable {
            override fun run() {
                invalidate()
                postDelayed(this, 20)  // Update every 20 milliseconds for smoother motion
            }
        }
        post(ticker)
    }
}
