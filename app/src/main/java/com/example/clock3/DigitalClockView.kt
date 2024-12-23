package com.example.clock3

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.Typeface
import android.util.AttributeSet
import android.view.View

class DigitalClockView : View {
    constructor(context: Context) : super(context) {
        init()
    }

    constructor(context: Context, attrs: AttributeSet?) : super(context, attrs) {
        init()
    }

    constructor(context: Context, attrs: AttributeSet?, defStyleAttr: Int) : super(
        context,
        attrs,
        defStyleAttr
    ) {
        init()
    }

    private fun init() {
        // Initialize the paint object
        paint = Paint()
        // Set the color of the paint object
        paint.color = Color.BLACK
        // Set the text size of the paint object
        paint.textSize = 100f
        // Set the typeface of the paint object
        paint.typeface = Typeface.DEFAULT_BOLD
        // Set the text alignment of the paint object
        paint.textAlign = Paint.Align.CENTER
        // Set the anti aliasing of the paint object
        paint.isAntiAlias = true
        // Set the style of the paint object
        paint.style = Paint.Style.FILL
        // Set the stroke width of the paint object
        paint.strokeWidth = 10f
        // Set the shadow layer of the paint object
        paint.setShadowLayer(10f, 10f, 10f, Color.GRAY)
        // Set the text of the paint object
        text = "12:00"
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        // Draw the text on the canvas
        canvas.drawText(text, width / 2f, height / 2f, paint)
    }

    // The paint object
    private lateinit var paint: Paint

    // The text
    private lateinit var text: String
}