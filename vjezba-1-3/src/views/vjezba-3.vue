<template>
  <div class="row text-center no-gutters">
    <div class="col-12">
      <span style="font-size: 20px" class="badge badge-pill badge-primary"
        >Vježba 3</span
      >
    </div>
    <div class="col-12 mt-5">
      <img :src="require('../assets/elevator-diagram.png')" />
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "Home"
});
</script>
