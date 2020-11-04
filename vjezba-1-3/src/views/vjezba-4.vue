<template>
  <div class="row no-gutters mx-5 justify-content-center">
    <div class="col-8">
      <div class="row">
        <div class="col-12 text-center">
          <group-box title="Dijagram">
            <img :src="require('@/assets/decorator-diagram.png')" />
          </group-box>
        </div>
        <div class="col-12 mt-4">
          <div class="row">
            <div class="col-6">
              <group-box title="Implementacija">
                <div v-html="content" />
              </group-box>
            </div>
            <div class="col-6">
              <group-box title="Ispis">
                <div style="font-size: 18px" v-html="output" />
              </group-box>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "vjezba-4",
  setup() {
    const content = `
<div style="font-family: Consolas, &quot;Courier New&quot;, monospace; line-height: 19px; white-space: pre;"><div><span style="color: #0000ff;">#include&nbsp;</span><span style="color: #a31515;">&lt;string&gt;</span></div><div><span style="color: #0000ff;">#include&nbsp;</span><span style="color: #a31515;">&lt;iostream&gt;</span></div><div><span style="color: #0000ff;">#include&nbsp;</span><span style="color: #a31515;">&lt;memory&gt;</span></div><br><div><span style="color: #0000ff;">using</span>&nbsp;<span style="color: #0000ff;">namespace</span>&nbsp;std;</div><br><div><span style="color: #0000ff;">class</span>&nbsp;Napitak</div><div>{</div><div><span style="color: #0000ff;">public:</span></div><div>&nbsp;&nbsp;<span style="color: #0000ff;">virtual</span>&nbsp;string&nbsp;opis()&nbsp;<span style="color: #0000ff;">const</span>&nbsp;{&nbsp;<span style="color: #0000ff;">return</span>&nbsp;_opis;&nbsp;}</div><div>&nbsp;&nbsp;<span style="color: #0000ff;">virtual</span>&nbsp;<span style="color: #0000ff;">double</span>&nbsp;cijena()&nbsp;<span style="color: #0000ff;">const</span>&nbsp;=&nbsp;<span style="color: #098658;">0</span>;</div><br><div><span style="color: #0000ff;">protected:</span></div><div>&nbsp;&nbsp;string&nbsp;_opis;</div><div>};</div><br><div><span style="color: #0000ff;">class</span>&nbsp;TurskaKava&nbsp;:&nbsp;<span style="color: #0000ff;">public</span>&nbsp;Napitak</div><div>{</div><div><span style="color: #0000ff;">public:</span></div><div>&nbsp;&nbsp;TurskaKava()</div><div>&nbsp;&nbsp;{</div><div>&nbsp;&nbsp;&nbsp;&nbsp;_opis&nbsp;=&nbsp;<span style="color: #a31515;">"turska-kava"</span>;</div><div>&nbsp;&nbsp;}</div><div>&nbsp;&nbsp;<span style="color: #0000ff;">virtual</span>&nbsp;<span style="color: #0000ff;">double</span>&nbsp;cijena()&nbsp;<span style="color: #0000ff;">const</span>&nbsp;{&nbsp;<span style="color: #0000ff;">return</span>&nbsp;<span style="color: #098658;">8</span>;&nbsp;}</div><div>};</div><br><div><span style="color: #0000ff;">class</span>&nbsp;Dodatak&nbsp;:&nbsp;<span style="color: #0000ff;">public</span>&nbsp;Napitak</div><div>{</div><div><span style="color: #0000ff;">public:</span></div><div>&nbsp;&nbsp;<span style="color: #0000ff;">virtual</span>&nbsp;string&nbsp;opis()&nbsp;=&nbsp;<span style="color: #098658;">0</span>;</div><div>};</div><br><div><span style="color: #0000ff;">class</span>&nbsp;Rum&nbsp;:&nbsp;<span style="color: #0000ff;">public</span>&nbsp;Dodatak</div><div>{</div><div><span style="color: #0000ff;">public:</span></div><div>&nbsp;&nbsp;Rum(shared_ptr&lt;Napitak&gt;&nbsp;napitak)&nbsp;:&nbsp;_napitak{napitak}</div><div>&nbsp;&nbsp;{</div><div>&nbsp;&nbsp;&nbsp;&nbsp;_opis&nbsp;=&nbsp;_napitak-&gt;opis()&nbsp;+&nbsp;<span style="color: #a31515;">";&nbsp;rum"</span>;</div><div>&nbsp;&nbsp;}</div><div>&nbsp;&nbsp;string&nbsp;opis()&nbsp;{&nbsp;<span style="color: #0000ff;">return</span>&nbsp;_opis;&nbsp;}</div><div>&nbsp;&nbsp;<span style="color: #0000ff;">double</span>&nbsp;cijena()&nbsp;<span style="color: #0000ff;">const</span>&nbsp;{&nbsp;<span style="color: #0000ff;">return</span>&nbsp;<span style="color: #098658;">6.5</span>&nbsp;+&nbsp;_napitak-&gt;cijena();&nbsp;}</div><br><div><span style="color: #0000ff;">private:</span></div><div>&nbsp;&nbsp;shared_ptr&lt;Napitak&gt;&nbsp;_napitak;</div><div>};</div><br><div><span style="color: #0000ff;">int</span>&nbsp;main()</div><div>{</div><div>&nbsp;&nbsp;shared_ptr&lt;Napitak&gt;&nbsp;napitak2&nbsp;=&nbsp;make_shared&lt;TurskaKava&gt;();</div><div>&nbsp;&nbsp;napitak2&nbsp;=&nbsp;make_shared&lt;Rum&gt;(napitak2);</div><br><div>&nbsp;&nbsp;cout&nbsp;&lt;&lt;&nbsp;napitak2-&gt;opis()&nbsp;&lt;&lt;&nbsp;endl</div><div>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;&lt;&nbsp;napitak2-&gt;cijena()&nbsp;&lt;&lt;&nbsp;endl;</div><br><div>&nbsp;&nbsp;<span style="color: #0000ff;">return</span>&nbsp;<span style="color: #098658;">0</span>;</div><div>}</div></div>`;
    const output = `<div style="color: rgb(171, 178, 191); background-color: rgb(40, 44, 52); font-family: Consolas, &quot;Courier New&quot;, monospace; line-height: 19px; white-space: pre;"><div style="line-height: 19px;"> &gt;&nbsp;turska-kava;&nbsp;rum&nbsp;14.5</div></div>`;

    return { content, output };
  }
});
</script>
